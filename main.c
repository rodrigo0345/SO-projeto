#include "./header.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void get_processos(FileArray *result, const FileArray all_files) {
  int size = 0;
  for (int i = 0; i < all_files.size; i++) {
    if (all_files.files[i].name[0] >= '0' &&
        all_files.files[i].name[0] <= '9') {
      result->files[size++] = all_files.files[i];
    }
  }
  result->size = size;
}

void printFiles(const FileArray files) {
  int i = 0;
  for (int i = 0; i < files.size; i++) {
    printf("%s\n", files.files[i].name);
  }
}

long shr_total(char *process_id) {
  char *smaps_file = malloc(sizeof(char) * 2048);
  sprintf(smaps_file, "/proc/%s/smaps", process_id);
  const char *shared_mem = file_content_position(smaps_file, 0, 4);
  FILE *fp = fopen(smaps_file, "r");

  if (fp == NULL) {
    // printf("Error opening file %s\n", smaps_file);
    free(smaps_file);

    return NULL;
  }

  long accum = 0;
  long prev_clean = 0;
  long prev_dirty = 0;

  char buffer[1024];
  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    const char *clean = strstr(buffer, "Shared_Clean:");
    const char *dirty = strstr(buffer, "Shared_Dirty:");
    if (clean != NULL && dirty == NULL) {
      strtok((char *)clean, " ");
      clean = strtok(NULL, " ");
      prev_clean += atol(clean);
    } else if (clean == NULL && dirty != NULL) {
      strtok((char *)dirty, " ");
      dirty = strtok(NULL, " ");
      prev_dirty += atol(dirty);
    }

    if (prev_clean != 0 || prev_dirty != 0) {
      accum += prev_clean + prev_dirty;
      prev_clean = 0;
      prev_dirty = 0;
    }
  }

  fclose(fp);
  free(smaps_file);
  return accum;
}

SystemInfo getSystemInfo(void) {
  // Uptime
  FILE *uptimeFile = fopen("/proc/uptime", "r");
  int uptime_hours = 0;
  int uptime_minutes = 0;
  int uptime_seconds_remainder = 0;

  if (uptimeFile != NULL) {
    double uptime_seconds;
    fscanf(uptimeFile, "%lf", &uptime_seconds);
    fclose(uptimeFile);

    // Calculate uptime in hours, minutes, and seconds
    uptime_hours = uptime_seconds / 3600;
    uptime_minutes = (int)(uptime_seconds / 60) % 60;
    uptime_seconds_remainder = (int)uptime_seconds % 60;
  }

  // Load Average
  double oneMinute = 0, fiveMinutes = 0, fifteenMinutes = 0;
  FILE *loadAvgFile = fopen("/proc/loadavg", "r");
  if (loadAvgFile != NULL) {
    fscanf(loadAvgFile, "%lf %lf %lf", &oneMinute, &fiveMinutes,
           &fifteenMinutes);
    fclose(loadAvgFile);
  }

  // Number of Users
  int activeUsers = countActiveUsers();

  return (SystemInfo){
      .processes = NULL,
      .n_users = activeUsers,
      .uptime = {.hours = uptime_hours,
                 .minutes = uptime_minutes,
                 .seconds = uptime_seconds_remainder},
      .load = {.oneMinute = oneMinute,
               .fiveMinutes = fiveMinutes,
               .fifteenMinutes = fifteenMinutes},
      .total_tasks = 0,
      .running_tasks = 0,
  };
}

SystemInfo processSystemInfo(const FileArray processes) {

  SystemInfo sysInfo = getSystemInfo();

  ProcessInfoArray processInfoArray = {
      malloc(sizeof(ProcessInfo) * processes.size), 0};
  int final_array_size = 0;

  // pegar no PID, ir a /proc/PROCID/loginuid
  // ir a /etc/passwd e usando o UID, pegar no nome do utilizador
  char *file = malloc(sizeof(char) * 2048);
  for (int i = 0; i < processes.size; i++) {
    char name[2048];
    strcpy(name, processes.files[i].name);

    sprintf(file, "/proc/%s/loginuid", name);
    const char *user_id = file_content_position(file, 0, 1);

    sysInfo.total_tasks++;

    if (user_id == NULL) {
      continue;
    }

    char *username = malloc(sizeof(char) * 2048);
    if (strcmp(user_id, "4294967295") == 0) {
      sprintf(username, "%s", "root");
    } else {
      char *line = (char *)find_line_with("/etc/passwd", user_id, ":");
      char *user = strtok(line, ":");
      strcpy(username, user);
      free(line);
    }

    // ler a primeira linha do /proc/PROCID/stat
    // Nome do processo -> Campo 2
    sprintf(file, "/proc/%s/stat", name);
    const char *command = file_content_position(file, 0, 2);
    // NI (Nice time) -> Campo 19
    const char *nice_time = file_content_position(file, 0, 19);
    const char *pr = file_content_position(file, 0, 18);

    // VIRT (Memoria virtual) -> Campo 23
    const char *virt = file_content_position(file, 0, 23);
    long virt_mem = atol(virt) / 1024;

    // RES (Resident set size) -> Campo 24
    const char *res = file_content_position(file, 0, 24);

    // S ->  /proc/PROCID/status
    char path[1024];
    sprintf(path, "/proc/%s/status", name);
    FILE *st_fd = fopen(path, "r");

    if (st_fd == NULL) {
      fclose(st_fd);
      continue;
    }

    // descobrir se o processo está a correr ou não
    char status[256];
    int running = 0;
    char *s = malloc(sizeof(char) * 256);
    while (fscanf(st_fd, "%*s %s", status) == 1) {
      if (strcmp(status, "R") == 0) {
        sysInfo.running_tasks++;
        running = 1;
        s = "R";
        break;
      }
    }
    if (strcmp(s, "R") != 0)
      s = "S";

    // %CPU -> Calcular com Campo 14, 15, 16, 17
    // FALTA fazer checks de erros
    const char *utime = file_content_position(file, 0, 14);
    const char *stime = file_content_position(file, 0, 15);

    // children processes
    const char *cutime = file_content_position(file, 0, 16);
    const char *cstime = file_content_position(file, 0, 17);

    const char *starttime = file_content_position(file, 0, 22);
    const char *uptime = file_content_position("/proc/uptime", 0, 1);

    int total_time = atoi(utime) + atoi(stime) + atoi(cutime) + atoi(cstime);

    // Source de onde fui buscar o %CPU
    // https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat
    long hertz = sysconf(_SC_CLK_TCK);
    long time_elapsed_seconds =
        (long)(atoi(uptime) - (atoi(starttime) / hertz));
    double cpu_usage =
        100 * ((double)((double)total_time / hertz) / time_elapsed_seconds);
    // %MEM -> Calcular com Campo 23, 24
    const char *res_mem = file_content_position(file, 0, 24);
    double mem_usage = 100 * ((double)atol(res_mem) / virt_mem);
    // TIME+ -> Campo 22 (Não tenho a certeza se está correto)
    const char *time_plus = file_content_position(file, 0, 22);
    long time_plus_seconds = (long)(atol(time_plus) / hertz);
    long time_plus_minutes = time_plus_seconds / 60;
    long time_plus_hours = time_plus_minutes / 60;
    // SHR (Shared mem) -> ir a /proc/PROCID/smaps
    long shr = shr_total(name);

    Time t = {time_plus_hours % 60, time_plus_minutes % 60,
              time_plus_seconds % 60};
    char *pid = malloc(sizeof(char) * 2048);
    strcpy(pid, processes.files[i].name);

    // Só para ficar como o "top" mesmo xD
    if (cpu_usage < 0.1 && cpu_usage > 0.05)
      cpu_usage = 0.1;
    if (mem_usage < 0.1 && mem_usage > 0.01)
      mem_usage = 0.1;

    ProcessInfo info = {.shr = shr,
                        .cpu_usage = cpu_usage,
                        .mem_usage = mem_usage,
                        .time = t,
                        .command = command,
                        .s = s,
                        .virt = virt_mem,
                        .res = res_mem,
                        .ni = nice_time,
                        .user = username,
                        .pid = pid,
                        .running = running,
                        .pr = (char *)pr};
    processInfoArray.processes[final_array_size++] = info;
  }
  free(file);
  processInfoArray.size = final_array_size;
  sysInfo.processes = processInfoArray;
  return sysInfo;
}

// dá print com base no comparator
void printProcesses(const ProcessInfoArray processes, void *comparator,
                    int limit) {
  qsort(processes.processes, processes.size, sizeof(ProcessInfo), comparator);
  printf("\n%7s %-9s %-3s %s %7s %6s %6s %s %5s %5s %9s  %2s\n", "PID", "USER",
         "PR", "NI", "VIRT", "RES", "SHR", "S", "%CPU", "%MEM", "TIME+",
         "COMMAND");
  for (int i = 0; i < limit && i < processes.size - 1; i++) {
    ProcessInfo info = processes.processes[i];

    if (str_length(info.user) > 8) {
      info.user[8] = '\0';
      info.user[7] = '+';
    }

    char *time = malloc(sizeof(char) * 512);
    sprintf(time, "%ld:%02ld.%02ld", info.time.hours, info.time.minutes,
            info.time.seconds);
    printf("%7s %-9s %-3s %2s %7ld %6s %6ld %s %5.1f %5.1f %9s  %2s\n",
           info.pid, info.user, info.pr, info.ni, info.virt, info.res, info.shr,
           info.s, info.cpu_usage, info.mem_usage, time, info.command);
    free(time);
  }
}

void printSystemStatus(SystemInfo sysInfo) {
  printf("top - %02ld:%02ld:%02ld up, %d user, load average: %02.2f %02.2f "
         "%02.2f\n",
         sysInfo.uptime.hours, sysInfo.uptime.minutes, sysInfo.uptime.seconds,
         sysInfo.n_users, sysInfo.load.oneMinute, sysInfo.load.fiveMinutes,
         sysInfo.load.fifteenMinutes);
  printf("tasks: %ld total, %ld running\n", sysInfo.total_tasks,
         sysInfo.running_tasks);
}

int compare_cpu_usage(const void *a, const void *b) {
  ProcessInfo *info_a = (ProcessInfo *)a;
  ProcessInfo *info_b = (ProcessInfo *)b;
  switch (info_a->running) {
  case 0:
    if (info_b->running == 1)
      return 1;
    if (info_a->cpu_usage < info_b->cpu_usage) {
      return 1;
    } else if (info_a->cpu_usage > info_b->cpu_usage) {
      return -1;
    } else {
      return 0;
    }
    break;
  default:
    if (info_b->running == 0)
      return -1;
    if (info_a->cpu_usage < info_b->cpu_usage) {
      return 1;
    } else if (info_a->cpu_usage > info_b->cpu_usage) {
      return -1;
    } else {
      return 0;
    }
  }
}

void execute_program_sync(SubProgram *program, int pid) {

  // get the first command
  trimString(program->argv);
  char **f = str_split(program->argv, ' ');
  char **aux_iter = f;

  // Find the last element in argv
  while (*aux_iter != NULL) {
    if (strcmp(*aux_iter, "") == 0) {
      *aux_iter = NULL;
      break;
    }
    aux_iter++;
  }
  // printf("Executing program: %s %s %s %s\n", f[0], f[1], f[2], f[3]);
  execvp(f[0], f);

  // If execvp fails, print an error message
  perror("execvp");
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {

  if (argc == 2 && !strcmp(argv[1], "top")) {

    FileArray *fileArray = malloc(sizeof(FileArray));
    FileArray *processes = malloc(sizeof(FileArray));

    while (1) {
      // clear the screen
      printf("\e[1;1H\e[2J");
      listFiles(fileArray, "/proc");
      processes->files = malloc(sizeof(File) * fileArray->size);

      // filtramos as pastas que sao processos, sendo o nome destas
      // pastas, numeros referentes ao seu pid
      get_processos(processes, *fileArray);
      SystemInfo sys = processSystemInfo(*processes);

      printSystemStatus(sys);
      printProcesses(sys.processes, compare_cpu_usage, 20);

      for (int i = 0; i < sys.processes.size; i++) {
        free((void *)sys.processes.processes[i].pid);
        free((void *)sys.processes.processes[i].user);
      }
      free(processes->files);
      sleep(1);
    }
    free((void *)fileArray->files);
    free((void *)fileArray);
  } else {
    // Programa das pipes
    SubProgram **programs_string = parse(argv, argc);
    int num_tasks = count_programs(programs_string) - 1;

    Pipe pipes[num_tasks];
    for (int i = 0; i < num_tasks; i++) {
      pipes[i] = *new_pipe();
    }

    SubProgram *output_file = &(SubProgram){.argv = NULL, .op = OUTPUT};
    int input_fd = STDIN_FILENO;
    int output_fd = STDOUT_FILENO;

    for (int i = 0; i < num_tasks + 1; i++) {
      Pipe *prev = i == 0 ? NULL : &pipes[i - 1];
      Pipe *next = programs_string[i]->op == LAST ? NULL : &pipes[i];

      if (programs_string[i]->op == OUTPUT) {
        output_file->argv = programs_string[i]->argv;
        continue;
      }

      // redirecionar o output para o ficheiro
      if (output_file->argv != NULL && i == num_tasks) {
        int fd = get_fd(output_file);
        next = new_pipe();
        next->fd[1] = fd;
      }

      int pid1 = create_process_run(programs_string[i], execute_program_sync,
                                    prev, next, output_fd, input_fd);

      if (pid1 < 0) {
        exit(EXIT_FAILURE);
      }
    }
  }
}

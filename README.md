# taskmaster :+1:
This project is about to reimplement in `C` some of [Supervisor](http://supervisord.org)'s functionality.
Client/server archictecture to allow for two separate programs: A daemon, that does the actual job control, and a control program, that provides a shell for the user, and communicates with the daemon over TCP sockets.
## The server 
* The part of the program can to start jobs as child processes, and keep them alive, restarting them if necessary. It also knows at all times if these processes are alive or dead.
* Information on which programs must be started, how, how many, if they must be restarted, etc... must containes in a configuration file, the format of which is `YAML`. This configuration must be loaded at launch, and can be reloadable, while taskmaster is running, by sending a SIGHUP to it. When it is reloaded, your program is expected to effect all the necessary changes to its run state (Removing programs, adding some, changing their monitoring conditions, etc ...), but it does NOT de-spawn processes that haven’t been changed in the reload.
* The configuration file allows the user to specify the following, for each program that is to be supervised:
  * The command to use to launch the program
  * The number of processes to start and keep running
  * Whether to start this program at launch or not
  * Whether the program should be restarted always, never, or on unexpected exits only
  * Which return codes represent an "expected" exit status
  * How long the program should be running after it’s started for it to be considered "successfully started"
  * How many times a restart should be attempted before aborting
  * Which signal should be used to stop (i.e. exit gracefully) the program
  * How long to wait after a graceful stop before killing the program
  * Options to discard the program’s stdout/stderr or to redirect them to files
  * Environment variables to set before launching the program
  * A working directory to set before launching the program
  * An umask to set before launching the program
* The server has a logging system that logs events to a local file (When a program is started, stopped, restarted, when it dies unexpectedly, when the configuration is reloaded, etc ...)
* More advanced logging/reporting facilities via email.
## The Client
* When the server is started, your the client provides a control shell to the user. It doesn't a fully-fledged shell like bash, but it has line editing, history and completion.
* This client shell allows the user to:
  * See the status of all the programs described in the config file (`status` command)
  * `start` / `stop` / `restart` programs
  * Reload the configuration file without stopping the main program
  * Stop the main program

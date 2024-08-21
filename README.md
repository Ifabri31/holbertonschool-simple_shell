<h1>Simple Shell</h1>

<p>For this project, we had to recreate a terminal that can receive and interpret commands. To achieve this, we used several functions created by ourselves as well as some that were provided by the standard library.</p>
  <p>Below, we will detail these functions, their use, and what they are for.</p>
   <h3>Getline:</h3>
   <p>We use this function to obtain the input read by the user. It takes three arguments, a pointer to pointer to char (where the line of text read will be stored), a pointer to a size (which represents the buffer size), and an FILE object (which represents the input stream).</p>
   <h3>**Tokenizar:</h3>
   <p>We use this function to indicate which delimiters we should pay attention to when entering a command. Within it, we include functions such as <strong>strtok</strong> and <strong>strdup</strong>, as well as a function created by us to count the number of delimiters that may be present.</p>
   <p>The <strong>strtok</strong> function is used to split a string into tokens based on the delimiters you specify. It works by finding a delimiter and inserting a null character ('\0') at the end of the current token. To get the next token, you need to call <strong>strtok</strong> with 'NULL' as the first argument, so it continues searching for delimiters where the last null character was placed</p>
   <p>The <strong>strdup</strong> function duplicates the given string. This is necessary because the original string is modified by <strong>strtok</strong> by inserting null characters at each delimiter, thus breaking the original string into separate tokens.</p>
   <h3>*command_in_path</h3>
    <p>This function searches for a command in the directories listed in the <code>PATH</code> environment variable. If the command is found and is executable, it returns the full path to the command. If the command is not found, it returns <code>NULL</code>.</p>
    <p>The <code>getenv</code> function is used to search for the <code>PATH</code> environment variable. Note that this is a provisional function, as we will be implementing our own version of <code>getenv</code> for this purpose.</p>
    <h3>Main function</h3>
     <p>This process allows the user to enter commands in an infinite loop. It executes these commands in child processes and manages command execution based on the directories specified in the <code>PATH</code> environment variable.</p>
     <p>This process allows the user to enter commands in an infinite loop. The loop, implemented with <code>while(1)</code>, continuously displays a prompt (<code>$ </code>) where the user can input commands. The commands are then executed in child processes based on the directories specified in the <code>PATH</code> environment variable.</p>
      <p>System calls were used:</p>
    <ul>
        <li><code>execve</code>: This call replaces the current process with a new process specified by the executable file. It is used to execute the command in the child process.</li>
        <li><code>fork</code>: This call creates a new process, known as the "child process." It is used to spawn a new process where the command will be executed.</li>
        <li><code>wait</code>: This call makes the parent process wait until all of its child processes have finished executing. It ensures that the parent process only continues once the child process has completed.</li>
    </ul>
    <p>To compile our program we use the following code:</p>
    
 <li><code>gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh</li</code>
   
   <p>This program is not completely finished yet, we need to create our getenv function, free memory, and solve possible errors in the terminal</p>

    <h2>Authors:</h2>
    <p>Mauricio Urroz  <a href="https://github.com/Mauriciourrozz" target="_blank"></p>
    <p>Fabrizzio Oviedo <a href="https://github.com/Ifabri31" target="_blank"></p>

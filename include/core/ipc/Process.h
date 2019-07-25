/*
 * Process.h
 *
 *  Created on: 24 июл. 2019 г.
 *      Author: sadko
 */

#ifndef CORE_IPC_PROCESS_H_
#define CORE_IPC_PROCESS_H_

#include <core/types.h>
#include <unistd.h>
#include <core/LSPString.h>
#include <data/cvector.h>

#ifdef PLATFORM_WINDOWS
    #include <processthreadsapi.h>
#endif /* PLATFORM_WINDOWS */

namespace lsp
{
    namespace ipc
    {
        /**
         * Class for running processes
         */
        class Process
        {
            private:
                Process & operator = (const Process &);

            private:
                enum pstatus_t {
                    PSTATUS_CREATED,
                    PSTATUS_RUNNING,
                    PSTATUS_EXITED
                };

                typedef struct envvar_t {
                    LSPString   name;
                    LSPString   value;
                } envvar_t;

            private:
                LSPString               sCommand;
                cvector<LSPString>      vArgs;
                cvector<envvar_t>       vEnv;
                pstatus_t               nStatus;
                int                     nExitCode;

#ifdef PLATFORM_WINDOWS
                PROCESS_INFORMATION     sPI;
#else
                pid_t                   nPID;
#endif
            protected:
                static void     do_clear_args(cvector<LSPString> *args);
                static void     do_clear_env(cvector<envvar_t> *env);

            public:
                explicit Process();
                ~Process();

            public:
                /**
                 * Set command for execution
                 * @param cmd command to execute
                 * @return status of operation
                 */
                status_t    set_command(const LSPString *cmd);

                /**
                 * Set command for execution
                 * @param cmd command to execute in UTF-8 encoding
                 * @return status of operation
                 */
                status_t    set_command(const char *cmd);

            public:
                /**
                 * Get overall number of additional command-line arguments
                 * @return number of additional command-line arguments
                 */
                size_t      args() const;

                /**
                 * Add argument at the end of command line
                 * @param value argument value
                 * @return status of operation
                 */
                status_t    add_arg(const LSPString *value);

                /**
                 * Add argument at the end of command line
                 * @param value argument value in UTF-8 encoding
                 * @return status of operation
                 */
                status_t    add_arg(const char *value);

                /**
                 * Set value of argument at the specified place
                 * @param value argument value
                 * @return status of operation
                 */
                status_t    set_arg(size_t index, const LSPString *value);

                /**
                 * Set value of argument at the specified place
                 * @param value argument value in UTF-8 encoding
                 * @return status of operation
                 */
                status_t    set_arg(size_t index, const char *value);

                /**
                 * Get value of argument at the specified place
                 * @param value pointer to store argument value
                 * @return status of operation
                 */
                status_t    get_arg(size_t index, LSPString *value);

                /**
                 * Get value of argument at the specified place
                 * @param value pointer to store argument value
                 * @return status of operation
                 */
                status_t    get_arg(size_t index, char **value);

                /**
                 * Remove the argument at the specified place
                 * @param value pointer to store value of removed argument
                 * @return status of operation
                 */
                status_t    remove_arg(size_t index, LSPString *value = NULL);

                /**
                 * Remove the argument at the specified place
                 * @param value pointer to store value of removed argument.
                 *        The pointer should be free()'d after use
                 * @return status of operation
                 */
                status_t    remove_arg(size_t index, char **value = NULL);

                /**
                 * Insert argument at the specified position
                 * @param value argument value
                 * @return status of operation
                 */
                status_t    insert_arg(size_t index, const LSPString *value);

                /**
                 * Insert argument at the specified position
                 * @param value argument value in UTF-8 encoding
                 * @return status of operation
                 */
                status_t    insert_arg(size_t index, const char *value);

                /**
                 * Clear arguments;
                 * @return status of operation
                 */
                status_t    clear_args();

            public:
                /**
                 * Return number of environment variables
                 * @return number of environment variables
                 */
                status_t    envs() const;

                /**
                 * Set value of the specific environment variable
                 * @param key the name of environment variable
                 * @param value the value of environment variable
                 * @return status of operation
                 */
                status_t    set_env(const LSPString *key, const LSPString *value);

                /**
                 * Set value of the specific environment variable
                 * @param key the name of environment variable in UTF-8 encoding
                 * @param value the value of environment variable in UTF-8 encoding
                 * @return status of operation
                 */
                status_t    set_env(const char *key, const char *value);

                /**
                 * Remove the specific environment variable
                 * @param key the name of environment variable
                 * @param pointer to store value of the removed environment variable
                 * @return status of operation
                 */
                status_t    remove_env(const LSPString *key, LSPString *value = NULL);

                /**
                 * Remove the specific environment variable
                 * @param key the name of environment variable in UTF-8 encoding
                 * @param pointer to store value of the removed environment variable in UTF-8 encoding.
                 *        The obtained pointer should be free()'d after use
                 * @return status of operation
                 */
                status_t    remove_env(const char *key, char **value = NULL);

                /**
                 * Obtain the value of the specific environment variable
                 * @param key the name of environment variable
                 * @param pointer to store value of the environment variable
                 * @return status of operation
                 */
                status_t    get_env(const LSPString *key, LSPString *value = NULL);

                /**
                 * Obtain the value of the specific environment variable
                 * @param key the name of environment variable in UTF-8 encoding
                 * @param pointer to store value of the environment variable in UTF-8 encoding.
                 *        The obtained pointer should be free()'d after use
                 * @return status of operation
                 */
                status_t    get_env(const char *key, char **value = NULL);

                /**
                 * Obtain the key and value of environment variable by index
                 * @param idx the environment variable index
                 * @param key environment variable key
                 * @param value environment variable value
                 * @return status of operation
                 */
                status_t    read_env(size_t idx, LSPString *key = NULL, LSPString *value = NULL);

                /**
                 * Obtain the value of the specific environment variable
                 * @param idx the environment variable index
                 * @param key the name of environment variable in UTF-8 encoding
                 *        The obtained pointer should be free()'d after use
                 * @param pointer to store value of the environment variable in UTF-8 encoding.
                 *        The obtained pointer should be free()'d after use
                 * @return status of operation
                 */
                status_t    read_env(size_t idx, char **key = NULL, char **value = NULL);

                /**
                 * Clear all environment variables
                 * @return status of operation
                 */
                status_t    clear_env();

            public:
                /**
                 * Copy environment variables of the current process
                 * @return status of operation
                 */
                status_t    copy_env();

                /**
                 * Launch the process
                 * @return status of operation
                 */
                status_t    launch();

                /**
                 * Check that process is in running state
                 * @return true if process is in running state
                 */
                bool        running();

                /**
                 * Check that process has exited
                 * @return true if process has exited
                 */
                bool        exited();

                /**
                 * Wait for the process termination
                 * @param millis number of milliseconds to wait, negative value means infinite wait
                 * @return status of operation
                 */
                status_t    wait(wsize_t millis);

                /**
                 * Get process exit status
                 * @param code pointer to save exit status
                 * @return status of operation
                 */
                status_t    exit_code(int *code);
        };
    
    } /* namespace ipc */
} /* namespace lsp */

#endif /* CORE_IPC_PROCESS_H_ */

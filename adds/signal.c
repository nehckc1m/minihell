// #include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//sig state (structure à inclure dans le .h, on est cependant pas obligé de procéder avec ça)
typedef struct s_shell_state 
{
    int last_signal;
    int running;
    char *line;
}   t_shell_state;

static t_shell_state *get_shell_state(void)
{
    static t_shell_state    state = {0, 1, NULL};
    return &state;
}

// prise en charge ctrl-c
void handle_sigint(int sig)
{
    t_shell_state   *state = get_shell_state();
    // printf("SIGINT (ctrl-c) num : %d\n", sig);
    state->last_signal = sig;
    printf("\n");  // Nouvelle ligne
    rl_on_new_line();               // Indique à readline qu'on est sur une nouvelle ligne
    rl_replace_line("", 0);         // Efface la ligne en cours
    rl_redisplay();                 // Réaffiche le prompt
}

// prise en charge ctrl-\ /
void handle_sigquit(int sig)
{
    t_shell_state   *state = get_shell_state();
    // printf("SIGQUIT (ctrl-\\) num : %d\n", sig);
    state->last_signal = sig;
}

void setup_signals(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    sigemptyset(&sa_int.sa_mask);
    sigemptyset(&sa_quit.sa_mask);
    sa_int.sa_flags = SA_RESTART;  // Permet de redémarrer certaines fonctions bloquantes
    sa_quit.sa_flags = SA_RESTART;
    // Associer les gestionnaires
    sa_int.sa_handler = handle_sigint;
    sa_quit.sa_handler = handle_sigquit;
    // Appliquer les gestionnaires aux signaux
    sigaction(SIGINT, &sa_int, NULL);
    sigaction(SIGQUIT, &sa_quit, NULL);
}

void restore_signals(void)
{
    struct sigaction    sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = SIG_DFL;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}

// pour que les signaux du dessus soient pris en charge lors de différentes commandes ou processus
void process_signals(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

// pour le tout petit ctrl-d
int handle_eof(t_shell_state *state)
{
    if (state->line == NULL)
    {
        // printf("EOF (ctrl-D)\n");
        write(STDERR_FILENO, "exit\n", 5);
        state->running = 0;
        return (1);
    }
    return (0);
}

/* int main(void)
{
    t_shell_state *state = get_shell_state();

    setup_signals(); // Configurer les gestionnaires de signaux

    while (state->running)
    {
        state->line = readline("minishell> ");

        if (handle_eof(state))
            break;

        if (state->line && *(state->line))
        {
            add_history(state->line);
            if (strcmp(state->line, "exit") == 0)
            {
                printf("[DEBUG] Exit command received\n");
                free(state->line);
                break;
            }
            printf("[DEBUG] Command entered: %s\n", state->line);
            printf("[DEBUG] Last signal received: %d\n", state->last_signal);
        }

        if (state->line)
            free(state->line);
    }

    printf("[TEST] Cleaning up and exiting...\n");
    restore_signals();
    rl_clear_history();

    return (0);
} */

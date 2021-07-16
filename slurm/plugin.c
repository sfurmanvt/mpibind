#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>
#include <mpibind.h>

#include <slurm/spank.h>

/*
 * All spank plugins must define this macro for the
 * Slurm plugin loader.
 */
SPANK_PLUGIN(mpibind, 1);

/*
 * Default option values
 */

static int opt_smt = -1;
static int opt_greedy = -1;
static int opt_gpu_optim = -1;
static int _opt_process_smt(int val, const char *optarg, int remote);
static int _opt_process_greedy(int val, const char *optarg, int remote);
static int _opt_process_gpu_optim(int val, const char *optarg, int remote);
static int _str2arg(const char *str, int *arg_ptr);

/*
 *  Provide options to srun:
 */
struct spank_option spank_options[] =
{
    { 
        "smt", 
        "[smt-level]", 
        "mpibind uses smt-level [smt-level]", 
        2, 
        0,
        (spank_opt_cb_f) _opt_process_smt
    },
    { 
        "greedy", 
        "[greedy]", 
        "Toggle greedy on and off with 1 and 0", 
        2, 
        0,
        (spank_opt_cb_f) _opt_process_greedy
    },
    { 
        "smt", 
        "[gpu_optim]", 
        "Toggle gpu optimization on and off with 1 and 0", 
        2, 
        0,
        (spank_opt_cb_f) _opt_process_smt
    },
    SPANK_OPTIONS_TABLE_END
};


/*
 *  Called from both srun and slurmd.
 */
int slurm_spank_init(spank_t sp, int ac, char **av)
{
    slurm_error ("I am a Hello World SPANK plugin");
    return ESPANK_SUCCESS;
}

static int _str2arg(const char *str, int *arg_ptr){
    long l;
    char *p = NULL;

    if (!str || str[0] == '\0')
        return -ESPANK_BAD_ARG;

    l = strtol(str, &p, 10);

    if (!p || (*p != '\0'))
        return -ESPANK_BAD_ARG;

    *arg_ptr = (int) l;

    return ESPANK_SUCCESS;
}

static int _opt_process_smt(int val, const char *optarg, int remote){
    int rc;

    if (optarg == NULL) {
        slurm_error("mpibind: invalid NULL argument!");
        return -ESPANK_BAD_ARG;
    }

    if ((rc = _str2arg(optarg, &opt_smt))) {
        slurm_error("Bad value for --smt: %s", optarg);
        return rc;
    }

    if (opt_smt < 0) {
        slurm_error("Bad value for --smt: %s", optarg);
        return -ESPANK_BAD_ARG;
    }

    return ESPANK_SUCCESS;
}

static int _opt_process_greedy(int val, const char *optarg, int remote){
    int rc;

    if (optarg == NULL) {
        slurm_error("mpibind: invalid NULL argument!");
        return -ESPANK_BAD_ARG;
    }

    if ((rc = _str2arg(optarg, &opt_greedy))) {
        slurm_error("Bad value for --greedy: %s", optarg);
        return rc;
    }

    if (opt_greedy != 0 && opt_greedy != 1) {
        slurm_error("Bad value for --greedy: %s", optarg);
        return -ESPANK_BAD_ARG;
    }

    return ESPANK_SUCCESS;
}

static int _opt_process_gpu_optim(int val, const char *optarg, int remote){
    int rc;

    if (optarg == NULL) {
        slurm_error("mpibind: invalid NULL argument!");
        return -ESPANK_BAD_ARG;
    }

    if ((rc = _str2arg(optarg, &opt_gpu_optim))) {
        slurm_error("Bad value for --gpu_optim: %s", optarg);
        return rc;
    }

    if (opt_gpu_optim != 0 && opt_gpu_optim != 1) {
        slurm_error("Bad value for --gpu_optim: %s", optarg);
        return -ESPANK_BAD_ARG;
    }

    return ESPANK_SUCCESS;
}
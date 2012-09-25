/* 
 * File:   mathtex.h
 * Author: oasynnoum
 *
 * Created on 2012/09/16, 12:37
 */

#ifndef MATHTEX_H
#define	MATHTEX_H

#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "http_log.h"
#include "ap_config.h"
#include "apr_strings.h"
#include "apr_file_io.h"
#include <apreq_param.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef WINDOWS
    #define DIRECTORY_SEPARATOR "\\"
#else
    #define DIRECTORY_SEPARATOR "/"
#endif


/* ---
 * timelimit -tWARNTIME -TKILLTIME
 * ------------------------------- */
#if !defined(KILLTIME)			/* no -DKILLTIME given... */
  #define NOKILLTIMESWITCH		/* ...remember that fact below */
  #if ISTIMELIMITSWITCH == 0		/* standalone timelimit disabled */
    #if defined(WARNTIME)		/* have WARNTIME but not KILLTIME */
      #define KILLTIME (WARNTIME)	/* so use WARNTIME for KILLTIME */
    #else				/* neither WARNTIME nor KILLTIME */
      #define KILLTIME (10)		/* default for built-in timelimit()*/
      /*#define KILLTIME (0)*/		/* disable until debugged */
    #endif
  #else					/* using standalone timelimit */
    #define KILLTIME (1)		/* always default -T1 killtime */
  #endif
#endif
#if !defined(WARNTIME)			/*no -DWARNTIME given for timelimit*/
  #if ISTIMELIMITSWITCH == 0		/* and no -DTIMELIMIT path either */
    #define WARNTIME (-1)		/* so standalone timelimit disabled*/
  #else					/*have path to standalone timelimit*/
    #if !defined(NOKILLTIMESWITCH)	/* have KILLTIME but not WARNTIME */
      #define WARNTIME (KILLTIME)	/* so use KILLTIME for WARNTIME */
      #undef  KILLTIME			/* but not for standalone killtime */
      #define KILLTIME (1)		/* default -T1 killtime instead */
    #else				/* neither KILLTIME nor WARNTIME */
      #define WARNTIME (10)		/* so default -t10 warntime */
    #endif
  #endif
#endif
/* ---
 * compile (or not) built-in timelimit() code
 * ------------------------------------------ */
#if ISTIMELIMITSWITCH==0 && KILLTIME>0	/*no -DTIMELIMIT, but have KILLTIME*/
  #define ISCOMPILETIMELIMIT 1		/* so we need built-in code */
#else
  #define ISCOMPILETIMELIMIT 0		/* else we don't need built-in code*/
#endif
#if ISCOMPILETIMELIMIT			/*header files, etc for timelimit()*/
  /* --- header files for timelimit() --- */
  #include <sys/signal.h>
  #include <sys/wait.h>
  #include <unistd.h>
  #include <signal.h>
  #include <sysexits.h>
  /*#define EX_OSERR	71*/		/* system error (e.g., can't fork) */
  #define HAVE_SIGACTION
#endif
    
#define MATHTEX_DIRECTIVE_LATEX "Latex"
#define MATHTEX_DIRECTIVE_PDFLATEX "Pdflatex"
#define MATHTEX_DIRECTIVE_DVIPNG "Dvipng"
#define MATHTEX_DIRECTIVE_DVIPS "Dvips"
#define MATHTEX_DIRECTIVE_PS2EPSI "Ps2epsi"
#define MATHTEX_DIRECTIVE_CONVERT "Convert"
#define MATHTEX_DIRECTIVE_TIMELIMIT "Timelimit"
#define MATHTEX_DIRECTIVE_TEXTAREA "Textarea"
#define MATHTEX_DIRECTIVE_HOME_DIR "HomeDir"
#define MATHTEX_DIRECTIVE_LATEX_METHOD "LatexMethod"
#define MATHTEX_DIRECTIVE_MESSAGE_LEVEL "MessageLevel"
    
typedef struct mathtex_config {
    char *latex_method;
    char *latex;
    char *pdflatex;
    char *dvipng;
    char *dvips;
    char *ps2epsi;
    char *convert;
    char *timelimit;
    char *textarea;
    char *home_dir;
    char *process_log_file_path;
    char *math_log_file_path;
    int message_level;
} mathtex_config_t;

typedef struct mathtex_object {
    int imagetype;
    int imagemethod;
    int latexmethod;
    int isdepth;
    char *query;
    mathtex_config_t *conf;
    request_rec *r;
    FILE *process_log_file;
    FILE *math_log_file;
} mathtex_object_t;

extern mathtex_object_t *mathtex_object_ctor(request_rec *r);
extern void mathtex_object_dtor(mathtex_object_t *o);
extern int mathtex_process(mathtex_object_t *o);
extern void mathtex_showmsg(const char *file, int line, int showlevel, char *label, char *data, mathtex_object_t *o);

module AP_MODULE_DECLARE_DATA mathtex_module;

#ifdef	__cplusplus
}
#endif

#endif	/* MATHTEX_H */


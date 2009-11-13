/* imtemplate.c
 * 
 * This is NOT a real input module but a (copy)-template to create one. Please
 * do NOT edit this file directly. Rather, copy it, together with the rest of 
 * the directory, to a new location ./plugins/im<yourname>, then replace
 * all references to imtemplate in Makefile.am to im<yourname>. Be sure to
 * fix the copyright notices to gain proper credit ;) Any derived version,
 * however, needs to be placed under GPLv3 (see GPLv3 for details). If you
 * do not like that policy, do not use this template or any of the header
 * files. The rsyslog project greatly appreciates module contributions, so
 * please consider contributing your work - even if you may think it only
 * server a single very special purpose. It has turned out that at least some
 * folks have similiar special purposes ;)
 *
 * IMPORTANT
 * The comments in this file are actually the interface specification. I decided
 * not to put it into a separate file as it is much simpler to keep it up to
 * date when it is part of the actual template module.
 *
 * NAMING
 * All input modules shall be named im<something>. While this is not a hard
 * requirement, it helps keeping track of things.
 *
 * Global variables and functions should have a prefix - use as somewhat
 * longer one to prevent conflicts with rsyslog itself and other modules
 * (OK, hopefully I'll have some more precise advise in the future...).
 *
 * INCLUDE MODULE IN THE MAIN MAKE SCRIPT
 * If the module shall be provided as part of rsyslog (or simply as a build aid,
 * you need to add it to the main autoconf files). To do so, you need to edit
 * Makefile.am and configure.ac in the main directory. Search for imtemplate
 * and copy/modify the relevant code for your plugin.
 *
 * DEBUGGING
 * While you develop your code, you may want to add
 *   --enable-debug --enable-rtinst
 * to your ./configure settings. These enable extra run-time checks, which cost
 * a lot of performance but can help detect some of the most frequently made
 * bugs. These settings will also provide you with a nice stack dump if something
 * goes really wrong.
 *
 * MORE SAMPLES
 * Remember that rsyslog ships with a number of input modules (./plugins/im*). It
 * is always a good idea to have a look at them before starting your own. imudp
 * may be a good, relatively trivial, sample.
 *
 * --------------------------------------------------------------------------------
 *
 * This template was cretead on 2008-02-01 by Rainer Gerhards.
 *
 * Copyright 2008 Rainer Gerhards and Adiscon GmbH.
 *
 * This file is part of rsyslog.
 *
 * Rsyslog is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Rsyslog is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Rsyslog.  If not, see <http://www.gnu.org/licenses/>.
 *
 * A copy of the GPL can be found in the file "COPYING" in this distribution.
 */
#include "config.h" /* this is for autotools and always must be the first include */
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>		/* do NOT remove: will soon be done by the module generation macros */
#include "rsyslog.h"		/* error codes etc... */
#include "cfsysline.h"		/* access to config file objects */
#include "module-template.h"	/* generic module interface code - very important, read it! */
#include "srUtils.h"		/* some utility functions */
#include "debug.h"		/* some debug helper functions */

MODULE_TYPE_INPUT	/* must be present for input modules, do not remove */

/* defines */

/* Module static data */
DEF_IMOD_STATIC_DATA	/* must be present, starts static data */

/* Here, define whatever static data is needed. Is it suggested that static variables only are
 * used (not externally visible). If you need externally visible variables, make sure you use a
 * prefix in order not to conflict with other modules or rsyslogd itself (also see comment
 * at file header).
 */
/* static int imtemplateWhateverVar = 0; */

/* config settings */


/* You may add any functions that you feel are useful for your needs. No specific restrictions
 * apply, but we suggest that you use the "iRet" call order, which enables you to use debug
 * support for your own functions and which also makes it easy to communicate exceptions back
 * to the upstream caller (rsyslog framework, for example.
 *
 * The function below is a sample of how one of your functions may look like. Again, the sample
 * below is *not* needed to be present in order to meet the interface requirements.
 *
 * Be sure to use static functions (suggested) or prefixes to prevent name conflicts -- see file
 * header for more information.
 */
static rsRetVal  /* rsRetVal is our generic error-reporting return type */
imtemplateMyFunc(int iMyParam)
{
	DEFiRet;	/* define iRet, the return code and other plumbing */
	/* define your local variables here */

	/* code whatever you need to code here. The "iRet" system can be helpful:
	 *
	 * CHKiRet(function(param1, param2, ...));
	 * 	calls a function and checks if it returns RS_RET_OK. If so, work
	 * 	proceeds. If some other code is returned, the function is aborted
	 * 	and control transferred to finalize_it (which you need to define)
	 *
	 * CHKiRet_Hdlr(function(param1, param2, ...))
	 * 	much like CHKiRet, but allows you to specify your own code that is
	 * 	executed if the function does not return RS_RET_OK, e.g.:
	 * 	CHKiRet_Hdlr(function(a, b)) {
	 * 		... some error handling here ...
	 * 	}
	 * 	control is not transferred to finalize_it, except if you use one
	 * 	of the relevant macros (described below)
	 *
	 * FINALIZE
	 * 	immediately transfers control to finalize_it, using the current
	 * 	value of iRet, e.g.
	 * 	if(bDone)
	 * 		FINALIZE;
	 *
	 * ABORT_FINALIZE(retcode)
	 * 	just like FINALIZE, except that iRet is set to the provided error
	 * 	code before control is transferred, e.g.
	 * 	if((ptr = MALLOC(20)) == NULL)
	 * 		ABORT_FINALIZE(RS_RET_OUT_OF_MEMORY);
	 *
	 * In order for all this to work, you need to define finalize_it, e.g.
	 *
	 * finalize_it:
	 * 	RETiRet;
	 *
	 * RETiRet does some housekeeping and then does a "return iRet" to transfer
	 * control back to the caller. There shall only be one function exit and
	 * it shall be via RETiRet, preferrably at the end of the function code.
	 *
	 */

finalize_it:
	/* clean up anything that needs to be cleaned up if processing did not
	 * go well, for example:
	 */
	if(iRet != RS_RET_OK) {
		/* cleanup, e.g.
		 * free(somePtr);
		 */
	}

	RETiRet;
}


/* This function is the cancel cleanup handler. It is called when rsyslog decides the
 * module must be stopped, what most probably happens during shutdown of rsyslogd. When
 * this function is called, the runInput() function (below) is already terminated - somewhere
 * in the middle of what it was doing. The cancel cleanup handler below should take
 * care of any locked mutexes and such, things that really need to be cleaned up
 * before processing continues. In general, many plugins do not need to provide
 * any code at all here.
 *
 * IMPORTANT: the calling interface of this function can NOT be modified. It actually is
 * called by pthreads. The provided argument is currently not being used.
 */
/* ------------------------------------------------------------------------------------------ *
 * DO NOT TOUCH the following code - it will soon be part of the module generation macros!    */
static void
inputModuleCleanup(void *arg)
{
	BEGINfunc
/* END no-touch zone                                                                          *
 * ------------------------------------------------------------------------------------------ */



	/* your code here */



/* ------------------------------------------------------------------------------------------ *
 * DO NOT TOUCH the following code - it will soon be part of the module generation macros!    */
	ENDfunc
}
/* END no-touch zone                                                                          *
 * ------------------------------------------------------------------------------------------ */


/* This function is called by the framework to gather the input. The module stays
 * most of its lifetime inside this function. It MUST NEVER exit this function. Doing
 * so would end module processing and rsyslog would NOT reschedule the module. If
 * you exit from this function, you violate the interface specification!
 *
 * So how is it terminated? When it is time to terminate, rsyslog actually cancels
 * the threads. This may sound scary, but is not. There is a cancel cleanup handler
 * defined (the function directly above). See comments there for specifics.
 *
 * runInput is always called on a single thread. If the module neees multiple threads,
 * it is free to create them. HOWEVER, it must make sure that any threads created
 * are killed and joined in the cancel cleanup handler.
 */
BEGINrunInput
	/* define any local variables you need here */
CODESTARTrunInput
	/* ------------------------------------------------------------------------------------------ *
	 * DO NOT TOUCH the following code - it will soon be part of the module generation macros!    */
	pthread_cleanup_push(inputModuleCleanup, NULL);
	while(1) { /* endless loop - do NOT break; out of it! */
	/* END no-touch zone                                                                          *
	 * ------------------------------------------------------------------------------------------ */

		/* your code here */

		/* All rsyslog objects (see other modules, e.g. msg.c) are available
		 * to your here. Some useful things are:
		 * 
		 * errmsg.LogError(NO_ERRCODE, format-string, ... params ...);
		 * 	logs an error message as syslogd, just as printf, e.g.
		 *         errmsg.LogError(NO_ERRCODE, "Error %d occured during %s", 1, "test");
		 *
		 * To submit the message to the queue engine, we must create the message
		 * object and fill it with data. If it contains a syslog message that must
		 * be parsed, we can add a flag that requests parsing. Otherwise, we must
		 * fill the properties ourselves. That is appropriate if the message 
		 * does not need to be parsed, for example when reading text (log) files. In that way,
		 * we can set the message properties as of our liking. This is how it works:
		 *
		msg_t *pMsg;
		CHKiRet(msgConstruct(&pMsg));
		MsgSetRawMsg(pMsg, msg);
		MsgSetHOSTNAME(pMsg, LocalHostName);
		MsgSetTAG(pMsg, "rsyslogd:");
		pMsg->iFacility = LOG_FAC(pri);
		pMsg->iSeverity = LOG_PRI(pri);
		flags |= INTERNAL_MSG;
		logmsg(pMsg, flags); / * some time, CHKiRet() will work here, too [today NOT!] * /
		 * 
		 * NOTE: for up-to-date usage samples, see the other provided input modules.
		 * A good starting point is probably imuxsock.
		 *
		 * This example probably does not set all message properties (but the ones
		 * that are of practical importance). If you need all, check msg.h. Use
		 * method access functions whereever possible, unfortunately not all structure
		 * members are currently exposed in that clean way - so you sometimes need
		 * to access them directly (it goes without saying that we will fix that
		 * over time ;)).
		 */

	/* ------------------------------------------------------------------------------------------ *
	 * DO NOT TOUCH the following code - it will soon be part of the module generation macros!    */
	}
	/*NOTREACHED*/
	
	pthread_cleanup_pop(0); /* just for completeness, but never called... */
	RETiRet;	/* use it to make sure the housekeeping is done! */
ENDrunInput
	/* END no-touch zone                                                                          *
	 * ------------------------------------------------------------------------------------------ */


/* The function is called by rsyslog before runInput() is called. It is a last chance
 * to set up anything specific. Most importantly, it can be used to tell rsyslog if the
 * input shall run or not. The idea is that if some config settings (or similiar things)
 * are not OK, the input can tell rsyslog it will not execute. To do so, return
 * RS_RET_NO_RUN or a specific error code. If RS_RET_OK is returned, rsyslog will
 * proceed and call the runInput() entry point. If you do not return anything
 * specific, RS_RET_OK is automatically returned (as in all functions).
 */
BEGINwillRun
	/* place any variables needed here */
CODESTARTwillRun

	/* ... your code here ... */

	/* Just to give you an idea, here are some samples (from the actual imudp module:
	 *
	if(udpLstnSocks == NULL)
		ABORT_FINALIZE(RS_RET_NO_RUN);

	if((pRcvBuf = MALLOC(glbl.GetMaxLine * sizeof(char))) == NULL) {
		ABORT_FINALIZE(RS_RET_OUT_OF_MEMORY);
	}
	*
	*/
finalize_it:
ENDwillRun


/* This function is called by the framework after runInput() has been terminated. It
 * shall free any resources and prepare the module for unload.
 *
 * So it is important that runInput() keeps track of what needs to be cleaned up.
 * Objects to think about are files (must be closed), network connections, threads (must
 * be stopped and joined) and memory (must be freed). Of course, there are a myriad
 * of other things, so use your own judgement what you need to do.
 *
 * Another important chore of this function is to persist whatever state the module
 * needs to persist. Unfortunately, there is currently no standard way of doing that.
 * Future version of the module interface will probably support it, but that doesn't
 * help you right at the moment. In general, it is suggested that anything that needs
 * to be persisted is saved in a file, whose name and location is passed in by a
 * module-specific config directive.
 */
BEGINafterRun
	/* place any variables needed here */
CODESTARTafterRun

	/* ... do cleanup here ... */

	/* if you have a string config variable, remember to free its content:
	 *
	if(pszStr != NULL) {
		free(pszStr);
		pszStr = NULL;
	}
	*/
ENDafterRun


/* The following entry points are defined in module-template.h.
 * In general, they need to be present, but you do NOT need to provide
 * any code here.
 */
BEGINmodExit
CODESTARTmodExit
ENDmodExit


BEGINqueryEtryPt
CODESTARTqueryEtryPt
CODEqueryEtryPt_STD_IMOD_QUERIES
ENDqueryEtryPt


/* The following function shall reset all configuration variables to their
 * default values. The code provided in modInit() below registers it to be
 * called on "$ResetConfigVariables". You may also call it from other places,
 * but in general this is not necessary. Once runInput() has been called, this
 * function here is never again called.
 */
static rsRetVal resetConfigVariables(uchar __attribute__((unused)) *pp, void __attribute__((unused)) *pVal)
{
	DEFiRet;

	/* if you have string variables in you config settings, you need to do this:
	if(pszStr != NULL) {
		free(pszStr);
		pszStr = NULL;
	}
	* Note that it is vitally important that the pointer is set to NULL, because
	* otherwise the framework handler will try to free it a second time when
	* a new value is set!
	*/


	/* ... your code here ... */


	RETiRet;
}


/* modInit() is called once the module is loaded. It must perform all module-wide
 * initialization tasks. There are also a number of housekeeping tasks that the
 * framework requires. These are handled by the macros. Please note that the
 * complexity of processing is depending on the actual module. However, only
 * thing absolutely necessary should be done here. Actual app-level processing
 * is to be performed in runInput(). A good sample of what to do here may be to
 * set some variable defaults. The most important thing probably is registration
 * of config command handlers.
 */
BEGINmodInit()
CODESTARTmodInit
	*ipIFVersProvided = 1; /* interface spec version this module is written to (currently always 1) */
CODEmodInit_QueryRegCFSLineHdlr
	/* register config file handlers
	 * For details, see cfsysline.c/.h. The config file is automatically handled. In general,
	 * a pointer to a variable receiving the value and the config directive is to be supplied.
	 * A custom function pointer can only be provided, which then is called when the config
	 * directive appears. Limit this to cases where it is absolutely necessary. The
	 * STD_LOADABLE_MODULE_ID is a value that identifies the module. It is use to automatically
	 * unregister the module's config file handlers upon module unload. Do NOT use any other
	 * value for this parameter! Available Syntaxes (supported types) can be seen in cfsysline.h,
	 * the ecslCmdHdrlType enum has all that are currently defined.
	 *
	 * Config file directives should always be along the lines of
	 *
	 * 	$Input<moduleobject>ObjObjName
	 *
	 * An example would be $InputImtemplateRetriesMax. This is currently not enforced,
	 * but when we get to our new config file format and reader, this becomes quite
	 * important.
	 *
	 * Please note that config directives must be provided in lower case. The engine
	 * makes the mapping (what currently means case-insensitive comparison). The dollar
	 * sign is NOT part of the directive and thus not specified.
	 *
	 * Some samples:
	 *
	 * A hypothetical integer variable:
	 * CHKiRet(omsdRegCFSLineHdlr((uchar *)"inputimtemplatemessagenumber", 0, eCmdHdlrInt,
		NULL, &intVariable, STD_LOADABLE_MODULE_ID));
	 *
	 * and a hypothetical string variable:
	 * CHKiRet(omsdRegCFSLineHdlr((uchar *)"inputimtemplatemessagetext", 0, eCmdHdlrGetWord,
	 * 	NULL, &pszBindAddr, STD_LOADABLE_MODULE_ID));
	 */

	/* whenever config variables exist, they should be resettable via $ResetConfigVariables.
	 * The following line adds our handler for that. Note that if you do not have any config
	 * variables at all (unlikely, I think...), you can remove this handler.
	 */
	CHKiRet(omsdRegCFSLineHdlr((uchar *)"resetconfigvariables", 1, eCmdHdlrCustomHandler,
		resetConfigVariables, NULL, STD_LOADABLE_MODULE_ID));

	/* ... do whatever else you need to do, but keep it brief ... */

ENDmodInit
/*
 * vim:set ai:
 */

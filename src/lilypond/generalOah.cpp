/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#include <iomanip>      // setw, setprecision, ...

#include "setTraceOahIfDesired.h"
#ifdef TRACE_OAH
  #include "traceOah.h"
#endif

#include "generalOah.h"


using namespace std;

namespace MusicXML2
{

//_______________________________________________________________________________
S_generalOah gGeneralOah;
S_generalOah gGeneralOahUserChoices;

S_generalOah generalOah::create (
  S_oahHandler handler)
{
  generalOah* o = new generalOah (
    handler);
  assert(o!=0);

  return o;
}

generalOah::generalOah (
  S_oahHandler handler)
  : oahGroup (
    "General",
    "hg", "help-general",
R"()",
    kElementVisibilityAlways,
    handler)
{
  // append this options group to the options handler
  // if relevant
  if (handler) {
    handler->
      appendGroupToHandler (this);
  }

  // initialize it
  initializeGeneralOah (false);
}

generalOah::~generalOah ()
{}

void generalOah::initializeGeneralWarningAndErrorsOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup
    warningAndErrorHandlingSubGroup =
      oahSubGroup::create (
        "Warnings and errors",
        "hwae", "help-warnings-and-errors",
R"()",
        kElementVisibilityAlways,
        this);

  appendSubGroup (warningAndErrorHandlingSubGroup);

  // quiet

  fQuiet = boolOptionsInitialValue;

  warningAndErrorHandlingSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "q", "quiet",
R"(Don't issue any warning or error messages.)",
        "quiet",
        fQuiet));

  // don't show errors

  fDontShowErrors = boolOptionsInitialValue;

  warningAndErrorHandlingSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "dse", "dont-show-errors",
R"(Don't show errors in the log.)",
        "dontShowErrors",
        fDontShowErrors));

  // do not abort on errors

  fDontAbortOnErrors = boolOptionsInitialValue;

  warningAndErrorHandlingSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "daoe", "dont-abort-on-errors",
        replaceSubstringInString (
R"(Do not abort execution on errors and go ahead.
This may be useful when debugging EXECUTABLE.)",
          "EXECUTABLE",
          gExecutableOah->fHandlerExecutableName),
        "dontAbortOnErrors",
        fDontAbortOnErrors));

  // display the source code position

  fDisplaySourceCodePosition = boolOptionsInitialValue;

  warningAndErrorHandlingSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "dscp", "display-source-code-position",
        replaceSubstringInString (
R"(Display the source code file name and line number
in warning and error messages.
This is useful when debugging EXECUTABLE.)",
          "EXECUTABLE",
          gExecutableOah->fHandlerExecutableName),
        "displaySourceCodePosition",
        fDisplaySourceCodePosition));
}

void generalOah::initializeGeneralCPUUsageOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup
    CPUUsageSubGroup =
      oahSubGroup::create (
        "CPU usage",
        "hgcpu", "help-general-cpu-usage",
R"()",
      kElementVisibilityAlways,
      this);

  appendSubGroup (CPUUsageSubGroup);

  // CPU usage

  fDisplayCPUusage = boolOptionsInitialValue;

  CPUUsageSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "dcpuu", "display-cpu-usage",
R"(Write information about CPU usage to standard error.)",
        "displayCPUusage",
        fDisplayCPUusage));
}

void generalOah::initializeGeneralOah (
  bool boolOptionsInitialValue)
{
  // register translation date
  // ------------------------------------------------------

  {
    time_t      translationRawtime;
    struct tm*  translationTimeinfo;
    char buffer [80];

    time (&translationRawtime);
    translationTimeinfo = localtime (&translationRawtime);

    strftime (buffer, 80, "%A %F @ %T %Z", translationTimeinfo);
    fTranslationDate = buffer;
  }

  // warning and error handling
  // --------------------------------------
  initializeGeneralWarningAndErrorsOptions (
    boolOptionsInitialValue);

  // CPU usage
  // --------------------------------------
  initializeGeneralCPUUsageOptions (
    boolOptionsInitialValue);
}

S_generalOah generalOah::createCloneWithTrueValues ()
{
  S_generalOah
    clone =
      generalOah::create (
        nullptr);
      // nullptr not to have it inserted twice in the option handler

  // set the options handler upLink
  clone->fHandlerUpLink =
    fHandlerUpLink;

  // warning and error handling
  // --------------------------------------

  clone->fQuiet =
    fQuiet;
  clone->fDontShowErrors =
    fDontShowErrors;
  clone->fDontAbortOnErrors =
    fDontAbortOnErrors;
  clone->fDisplaySourceCodePosition =
    fDisplaySourceCodePosition;

  // CPU usage
  // --------------------------------------

  clone->fDisplayCPUusage = true;

  return clone;
}

  /* JMI
void generalOah::setAllGeneralTraceOah (
  bool boolOptionsInitialValue)
{
  // warning and error handling
  // --------------------------------------

  fQuiet = boolOptionsInitialValue;
  fDontShowErrors = boolOptionsInitialValue;
  fDontAbortOnErrors = boolOptionsInitialValue;
  fDisplaySourceCodePosition = boolOptionsInitialValue;

  // CPU usage
  // --------------------------------------

  fDisplayCPUusage = boolOptionsInitialValue;
}
  */

//______________________________________________________________________________
void generalOah::enforceQuietness ()
{
  fDisplayCPUusage = false; // JMI
}

//______________________________________________________________________________
void generalOah::checkOptionsConsistency ()
{
  // JMI
}

//______________________________________________________________________________
void generalOah::printGeneralOahValues (int fieldWidth)
{
  gLogOstream <<
    "The general options are:" <<
    endl;

  gIndenter++;

  // translation date
  // --------------------------------------

  gLogOstream << left <<

  gIndenter++;

  gLogOstream << left <<
    setw (fieldWidth) << "translationDate" << " : " <<
    fTranslationDate <<
    endl;

  gIndenter--;

  // warning and error handling
  // --------------------------------------

  gLogOstream << left <<
    setw (fieldWidth) << "Warning and error handling:" <<
    endl;

  gIndenter++;

  gLogOstream <<
    setw (fieldWidth) << "quiet" << " : " <<
    booleanAsString (fQuiet) <<
    endl <<
    setw (fieldWidth) << "dontShowErrors" << " : " <<
    booleanAsString (fDontShowErrors) <<
    endl <<
    setw (fieldWidth) << "dontAbortOnErrors" << " : " <<
    booleanAsString (fDontAbortOnErrors) <<
    endl <<
    setw (fieldWidth) << "displaySourceCodePosition" << " : " <<
    booleanAsString (fDisplaySourceCodePosition) <<
    endl;

  gIndenter--;


  // CPU usage
  // --------------------------------------

  gLogOstream << left <<
    setw (fieldWidth) << "CPU usage:" <<
    endl;

  gIndenter++;

  gLogOstream <<
    setw (fieldWidth) << "displayCPUusage" << " : " <<
    booleanAsString (fDisplayCPUusage) <<
    endl;

  gIndenter--;

  gIndenter--;
}

S_oahValuedAtom generalOah::handleAtom (
  ostream&  os,
  S_oahAtom atom)
{
  S_oahValuedAtom result;

  // JMI ???

  return result;
}

ostream& operator<< (ostream& os, const S_generalOah& elt)
{
  elt->print (os);
  return os;
}

//______________________________________________________________________________
void initializeGeneralOahHandling (
  S_oahHandler handler)
{
  // create the options variables
  // ------------------------------------------------------

  gGeneralOahUserChoices = generalOah::create (
    handler);
  assert(gGeneralOahUserChoices != 0);

  gGeneralOah =
    gGeneralOahUserChoices;

  gGeneralOah->
    checkOptionsConsistency ();
}


}
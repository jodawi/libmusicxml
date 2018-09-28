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

#include "msr.h"

#include "generalOptions.h"


using namespace std;

namespace MusicXML2 
{

//_______________________________________________________________________________
S_generalOptions gGeneralOptions;
S_generalOptions gGeneralOptionsUserChoices;

S_generalOptions generalOptions::create (
  S_optionsHandler optionsHandler)
{
  generalOptions* o = new generalOptions (
    optionsHandler);
  assert(o!=0);

  return o;
}

generalOptions::generalOptions (
  S_optionsHandler optionsHandler)
  : optionsGroup (
    "General",
    "hg", "help-general",
R"(Options that are used by various components of the library
are grouped here.)",
    optionsHandler)
{
  // append this options group to the options handler
  // if relevant
  if (optionsHandler) {
    optionsHandler->
      appendOptionsGroup (this);
  }

  // initialize it
  initializeGeneralOptions (false);
}

/*
    // exit after some passes
    fExit2a = boolOptionsInitialValue;
    fExit2b = boolOptionsInitialValue;
    fExit3 = boolOptionsInitialValue;

    // '-exit2a' is hidden...
    S_optionsBooleanItem
      exit2aOptionsBooleanItem =
        optionsBooleanItem::create (
          "e2a", "exit2a",
R"(Exit after pass 2a, i.e. after conversion
of the MusicXML tree to an MSR skeleton.)",
          "exit2a",
          fExit2a);
    exit2aOptionsBooleanItem->
      setOptionsElementIsHidden ();
      
    specificTraceSubGroup->
      appendOptionsItem (
        exit2aOptionsBooleanItem);

    // '-exit2b' is hidden...
    S_optionsBooleanItem
      exit2bOptionsBooleanItem =
        optionsBooleanItem::create (
          "e2b", "exit2b",
R"(Exit after pass 2b, i.e. after conversion
of the MusicXML tree to MSR.)",
          "exit2b",
          fExit2b);
    exit2bOptionsBooleanItem->
      setOptionsElementIsHidden ();
      
    specificTraceSubGroup->
      appendOptionsItem (
        exit2bOptionsBooleanItem);

    // '-exit3' is hidden...
    S_optionsBooleanItem
      exit3OptionsBooleanItem =
        optionsBooleanItem::create (
          "e3", "exit3",
R"(Exit after pass 3, i.e. after conversion
of the MSR to LPSR.)",
          "exit3",
          fExit3);
    exit3OptionsBooleanItem->
      setOptionsElementIsHidden ();
      
    specificTraceSubGroup->
      appendOptionsItem (
        exit3OptionsBooleanItem);



  // command line
  // --------------------------------------

  clone->fProgramName =
    fProgramName;
      
  clone->fCommandLineWithLongOptions =
    fCommandLineWithLongOptions;
  clone->fCommandLineWithShortOptions =
    fCommandLineWithShortOptions;

  
  // warning and error handling
  // --------------------------------------

  clone->fQuiet =
    fQuiet;
  clone->fIgnoreErrors =
    fIgnoreErrors;

    
  // CPU usage
  // --------------------------------------

  clone->fDisplayCPUusage = true;

    




  // CPU usage
  // --------------------------------------

  gLogIOstream << left <<
    setw (fieldWidth) << "CPU usage:" <<
    endl;

  gIndenter++;

  gLogIOstream <<
    setw (fieldWidth) << "displayCPUusage" << " : " <<
    booleanAsString (fDisplayCPUusage) <<
    endl;

  gIndenter--;
  
  */




generalOptions::~generalOptions ()
{}

void generalOptions::initializeGeneralOptions (
  bool boolOptionsInitialValue)
{
  // help
  // --------------------------------------

  {
    // variables  
    
    // options
  
    S_optionsSubGroup
      helpGeneralOptionsHelpSubGroup =
        optionsSubGroup::create (
          "Options help",
          "hgoh", "help-general-options-help",
R"()",
        optionsSubGroup::kAlwaysShowDescription,
        this);
  
    appendOptionsSubGroup (helpGeneralOptionsHelpSubGroup);
  
    helpGeneralOptionsHelpSubGroup->
      appendOptionsItem (
        optionsHelpUsageItem::create (
          "ho", "help-options",
R"(Print options usage help.)"));

    helpGeneralOptionsHelpSubGroup->
      appendOptionsItem (
        optionsHelpSummaryItem::create (
          "hs", "help-summary",
R"(Display a help summary and exit.)"));
  
    helpGeneralOptionsHelpSubGroup->
      appendOptionsItem (
        optionsItemHelpItem::create (
        "ih", "item-help",
R"(Print help about 'itemName'.)",
        "itemName"));
  }


  // warning and error handling
  // --------------------------------------

  {
    // variables
    
    fQuiet         = false;
    fIgnoreErrors  = false;
    fAbortOnErrors = false;
  
    // options
  
    S_optionsSubGroup
      warningAndErrorHandlingSubGroup =
        optionsSubGroup::create (
          "Warnings and errors",
          "hwae", "help-warnings-and-errors",
R"()",
          optionsSubGroup::kAlwaysShowDescription,
          this);
  
    appendOptionsSubGroup (warningAndErrorHandlingSubGroup);
  
    warningAndErrorHandlingSubGroup->
      appendOptionsItem (
        optionsBooleanItem::create (
          "q", "quiet",
R"(Don't issue any warning or error messages.)",
          "quiet",
          fQuiet));
  
    warningAndErrorHandlingSubGroup->
      appendOptionsItem (
        optionsBooleanItem::create (
          "i", "ignore-errors",
R"(Ignore errors and proceed.)",
          "ignoreErrors",
          fIgnoreErrors));
  
    warningAndErrorHandlingSubGroup->
      appendOptionsItem (
        optionsBooleanItem::create (
          "aoe", "abort-on-errors",
R"(Abort execution on errors instead of gracefully exiting.
This is useful when debugging xml2ly.)",
          "abortOnErrors",
          fAbortOnErrors));
  }


  // CPU usage
  // --------------------------------------

  {
    // variables  
  
    fDisplayCPUusage = boolOptionsInitialValue;
      
    // options
  
    S_optionsSubGroup
      CPUUsageSubGroup =
        optionsSubGroup::create (
          "CPU usage",
          "hgcpu", "help-general-cpu-usage",
R"()",
        optionsSubGroup::kAlwaysShowDescription,
        this);
  
    appendOptionsSubGroup (CPUUsageSubGroup);
        
    CPUUsageSubGroup->
      appendOptionsItem (
        optionsBooleanItem::create (
          "dcpuu", "display-cpu-usage",
R"(Write information about CPU usage to standard error.)",
          "displayCPUusage",
          fDisplayCPUusage));
  }


  // exit after some passes
  // --------------------------------------

  {
    // variables  
  
    // options
  
    S_optionsSubGroup
      exitAfterSomePassesSubGroup =
        optionsSubGroup::create (
          "Exit after some passes",
          "hge", "help-general-exit",
R"()",
        optionsSubGroup::kAlwaysShowDescription,
        this);
  
    appendOptionsSubGroup (exitAfterSomePassesSubGroup);
        
    // '-exit-2a' is hidden...
    S_optionsBooleanItem
      exit2aOptionsBooleanItem =
        optionsBooleanItem::create (
          "e2a", "exit-2a",
R"(Exit after pass 2a, i.e. after conversion
of the MusicXML tree to an MSR skeleton.)",
          "exit2a",
          fExit2a);
    exit2aOptionsBooleanItem->
      setOptionsElementIsHidden ();
      
    exitAfterSomePassesSubGroup->
      appendOptionsItem (
        exit2aOptionsBooleanItem);

    // '-exit-2b' is hidden...
    S_optionsBooleanItem
      exit2bOptionsBooleanItem =
        optionsBooleanItem::create (
          "e2b", "exit-2b",
R"(Exit after pass 2b, i.e. after conversion
of the MusicXML tree to MSR.)",
          "exit2b",
          fExit2b);
    exit2bOptionsBooleanItem->
      setOptionsElementIsHidden ();
      
    exitAfterSomePassesSubGroup->
      appendOptionsItem (
        exit2bOptionsBooleanItem);

    // '-exit-3' is hidden...
    S_optionsBooleanItem
      exit3OptionsBooleanItem =
        optionsBooleanItem::create (
          "e3", "exit-3",
R"(Exit after pass 3, i.e. after conversion
of the MSR to LPSR.)",
          "exit3",
          fExit3);
    exit3OptionsBooleanItem->
      setOptionsElementIsHidden ();
      
    exitAfterSomePassesSubGroup->
      appendOptionsItem (
        exit3OptionsBooleanItem);
  }
}

S_generalOptions generalOptions::createCloneWithTrueValues ()
{
  S_generalOptions
    clone =
      generalOptions::create (0);
      // 0 not to have it inserted twice in the option handler

  // set the options handler uplink
  clone->
    setOptionsHandlerUplink (
      fOptionsHandlerUplink);


  // command line
  // --------------------------------------

  clone->fProgramName =
    fProgramName;
      
  clone->fCommandLineWithLongOptions =
    fCommandLineWithLongOptions;
  clone->fCommandLineWithShortOptions =
    fCommandLineWithShortOptions;

  
  // display
  // --------------------------------------


  // warning and error handling
  // --------------------------------------

  clone->fQuiet =
    fQuiet;
  clone->fIgnoreErrors =
    fIgnoreErrors;

    
  // CPU usage
  // --------------------------------------

  clone->fDisplayCPUusage = true;


  return clone;
}

void generalOptions::printGeneralOptionsValues (int fieldWidth)
{  
  gLogIOstream <<
    "The general options are:" <<
    endl;

  gIndenter++;

/*
  // command line
  // --------------------------------------

  gLogIOstream << left <<

  gIndenter++;

  gLogIOstream << left <<
    setw (fieldWidth) << "input source name" << " : " <<
    fInputSourceName <<
    endl <<
      
    setw (fieldWidth) << "translation date" << " : " <<
    fTranslationDate <<
    endl;

  gIndenter--;

  // output file
  // --------------------------------------

  gLogIOstream << left <<
    setw (fieldWidth) << "Output file:" <<
    endl;

  gIndenter++;

  gLogIOstream << left <<        
    setw (fieldWidth) << "inputSourceName" << " : \"" <<
    fInputSourceName <<
    "\"" <<
    endl <<
    setw (fieldWidth) << "outputFileName" << " : \"" <<
    fOutputFileName <<
    "\"" <<
    endl;

  gIndenter--;
*/

  // display
  // --------------------------------------
  

  // CPU usage
  // --------------------------------------

  gLogIOstream << left <<
    setw (fieldWidth) << "CPU usage:" <<
    endl;

  gIndenter++;

  gLogIOstream <<
    setw (fieldWidth) << "displayCPUusage" << " : " <<
    booleanAsString (fDisplayCPUusage) <<
    endl;

  gIndenter--;
  
  gIndenter--;

  gIndenter--;
}

S_optionsItem generalOptions::handleOptionsItem (
  ostream&      os,
  S_optionsItem item)
{
  S_optionsItem result;
  
  return result;
}

ostream& operator<< (ostream& os, const S_generalOptions& elt)
{
  elt->print (os);
  return os;
}

//______________________________________________________________________________
void initializeGeneralOptionsHandling (
  S_optionsHandler optionsHandler)
{  
  // create the options variables
  // ------------------------------------------------------
  
  gGeneralOptionsUserChoices = generalOptions::create (
    optionsHandler);
  assert(gGeneralOptionsUserChoices != 0);

  gGeneralOptions =
    gGeneralOptionsUserChoices;
}


}

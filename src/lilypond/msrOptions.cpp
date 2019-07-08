/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#include <climits>      // INT_MIN, INT_MAX
#include <iomanip>      // setw, setprecision, ...
#include <sstream>

#include <regex>

#include "utilities.h"

#include "generalOptions.h"

#include "setTraceOptionsIfDesired.h"
#ifdef TRACE_OPTIONS
  #include "traceOptions.h"
#endif

#include "msrOptions.h"


using namespace std;

namespace MusicXML2
{

//______________________________________________________________________________
S_optionsPartRenameItem optionsPartRenameItem::create (
  string             shortName,
  string             longName,
  string             description,
  string             valueSpecification,
  string             optionsPartRenameItemVariableName,
  map<string, string>&
                     optionsPartRenameItemVariable)
{
  optionsPartRenameItem* o = new
    optionsPartRenameItem (
      shortName,
      longName,
      description,
      valueSpecification,
      optionsPartRenameItemVariableName,
      optionsPartRenameItemVariable);
  assert(o!=0);
  return o;
}

optionsPartRenameItem::optionsPartRenameItem (
  string             shortName,
  string             longName,
  string             description,
  string             valueSpecification,
  string             optionsPartRenameItemVariableName,
  map<string, string>&
                     optionsPartRenameItemVariable)
  : oahValuedAtom (
      shortName,
      longName,
      description,
      valueSpecification,
      optionsPartRenameItemVariableName),
    fOptionsPartRenameItemVariable (
      optionsPartRenameItemVariable)
{}

optionsPartRenameItem::~optionsPartRenameItem ()
{}

void optionsPartRenameItem::print (ostream& os) const
{
  const int fieldWidth = K_OPTIONS_FIELD_WIDTH;

  os <<
    "OptionsPartRenameItem:" <<
    endl;

  gIndenter++;

  printValuedAtomEssentials (
    os, fieldWidth);

  os << left <<
    setw (fieldWidth) <<
    "fVariableName" << " : " <<
    fVariableName <<
    setw (fieldWidth) <<
    "fOptionsPartRenameItemVariable" << " : " <<
    endl;

  if (! fOptionsPartRenameItemVariable.size ()) {
    os << "none";
  }
  else {
    map<string, string>::const_iterator
      iBegin = fOptionsPartRenameItemVariable.begin (),
      iEnd   = fOptionsPartRenameItemVariable.end (),
      i      = iBegin;
    for ( ; ; ) {
      os << (*i).first << " --> " << (*i).second;
      if (++i == iEnd) break;
      os << endl;
    } // for
  }

  os << endl;
}

void optionsPartRenameItem::printOptionsValues (
  ostream& os,
  int      valueFieldWidth) const
{
  os << left <<
    setw (valueFieldWidth) <<
    fVariableName <<
    " : ";

  if (! fOptionsPartRenameItemVariable.size ()) {
    os <<
      "none" <<
      endl;
  }
  else {
    os << endl;

    gIndenter++;

    map<string, string>::const_iterator
      iBegin = fOptionsPartRenameItemVariable.begin (),
      iEnd   = fOptionsPartRenameItemVariable.end (),
      i      = iBegin;
    for ( ; ; ) {
      os <<
        "\"" <<
        (*i).first <<
        "\" --> \"" <<
        (*i).second <<
        "\"" <<
        endl;
      if (++i == iEnd) break;
    } // for

    gIndenter--;
  }
}

ostream& operator<< (ostream& os, const S_optionsPartRenameItem& elt)
{
  elt->print (os);
  return os;
}

//______________________________________________________________________________
S_optionsPartTransposeItem optionsPartTransposeItem::create (
  string             shortName,
  string             longName,
  string             description,
  string             valueSpecification,
  string             optionsPartTransposeItemVariableName,
  map<string, S_msrSemiTonesPitchAndOctave>&
                     optionsPartTransposeItemVariable)
{
  optionsPartTransposeItem* o = new
    optionsPartTransposeItem (
      shortName,
      longName,
      description,
      valueSpecification,
      optionsPartTransposeItemVariableName,
      optionsPartTransposeItemVariable);
  assert(o!=0);
  return o;
}

optionsPartTransposeItem::optionsPartTransposeItem (
  string             shortName,
  string             longName,
  string             description,
  string             valueSpecification,
  string             optionsPartTransposeItemVariableName,
  map<string, S_msrSemiTonesPitchAndOctave>&
                     optionsPartTransposeItemVariable)
  : oahValuedAtom (
      shortName,
      longName,
      description,
      valueSpecification,
      optionsPartTransposeItemVariableName),
    fOptionsPartTransposeItemVariable (
      optionsPartTransposeItemVariable)
{}

optionsPartTransposeItem::~optionsPartTransposeItem ()
{}

void optionsPartTransposeItem::print (ostream& os) const
{
  const int fieldWidth = K_OPTIONS_FIELD_WIDTH;

  os <<
    "OptionsPartTransposeItem:" <<
    endl;

  gIndenter++;

  printValuedAtomEssentials (
    os, fieldWidth);

  os << left <<
    setw (fieldWidth) <<
    "fVariableName" << " : " <<
    fVariableName <<
    setw (fieldWidth) <<
    "fOptionsPartTransposeItemVariable" << " : " <<
    endl;

  if (! fOptionsPartTransposeItemVariable.size ()) {
    os << "none";
  }
  else {
    map<string, S_msrSemiTonesPitchAndOctave>::const_iterator
      iBegin = fOptionsPartTransposeItemVariable.begin (),
      iEnd   = fOptionsPartTransposeItemVariable.end (),
      i      = iBegin;
    for ( ; ; ) {
      os << (*i).first << " --> " << (*i).second;
      if (++i == iEnd) break;
      os << endl;
    } // for
  }

  os << endl;
}

void optionsPartTransposeItem::printOptionsValues (
  ostream& os,
  int      valueFieldWidth) const
{
  os << left <<
    setw (valueFieldWidth) <<
    fVariableName <<
    " : ";

  if (! fOptionsPartTransposeItemVariable.size ()) {
    os <<
      "none" <<
      endl;
  }
  else {
    os << endl;

    gIndenter++;

    map<string, S_msrSemiTonesPitchAndOctave>::const_iterator
      iBegin = fOptionsPartTransposeItemVariable.begin (),
      iEnd   = fOptionsPartTransposeItemVariable.end (),
      i      = iBegin;
    for ( ; ; ) {
      os <<
        "\"" <<
        (*i).first <<
        "\" --> \"" <<
        (*i).second <<
        "\"" <<
        endl;
      if (++i == iEnd) break;
    } // for

    gIndenter--;
  }
}

ostream& operator<< (ostream& os, const S_optionsPartTransposeItem& elt)
{
  elt->print (os);
  return os;
}

//______________________________________________________________________________
S_optionsMsrPitchesLanguageItem optionsMsrPitchesLanguageItem::create (
  string             shortName,
  string             longName,
  string             description,
  string             valueSpecification,
  string             optionsMsrPitchesLanguageKindItemVariableName,
  msrQuarterTonesPitchesLanguageKind&
                     optionsMsrPitchesLanguageKindItemVariable)
{
  optionsMsrPitchesLanguageItem* o = new
    optionsMsrPitchesLanguageItem (
      shortName,
      longName,
      description,
      valueSpecification,
      optionsMsrPitchesLanguageKindItemVariableName,
      optionsMsrPitchesLanguageKindItemVariable);
  assert(o!=0);
  return o;
}

optionsMsrPitchesLanguageItem::optionsMsrPitchesLanguageItem (
  string             shortName,
  string             longName,
  string             description,
  string             valueSpecification,
  string             optionsMsrPitchesLanguageKindItemVariableName,
  msrQuarterTonesPitchesLanguageKind&
                     optionsMsrPitchesLanguageKindItemVariable)
  : oahValuedAtom (
      shortName,
      longName,
      description,
      valueSpecification,
      optionsMsrPitchesLanguageKindItemVariableName),
    fOptionsMsrPitchesLanguageKindItemVariable (
      optionsMsrPitchesLanguageKindItemVariable)
{}

optionsMsrPitchesLanguageItem::~optionsMsrPitchesLanguageItem ()
{}

void optionsMsrPitchesLanguageItem::print (ostream& os) const
{
  const int fieldWidth = K_OPTIONS_FIELD_WIDTH;

  os <<
    "OptionsMsrPitchesLanguageItem:" <<
    endl;

  gIndenter++;

  printValuedAtomEssentials (
    os, fieldWidth);

  os << left <<
    setw (fieldWidth) <<
    "fVariableName" << " : " <<
    fVariableName <<
    endl <<
    setw (fieldWidth) <<
    "fOptionsMsrPitchesLanguageItemVariable" << " : \"" <<
    msrQuarterTonesPitchesLanguageKindAsString (
      fOptionsMsrPitchesLanguageKindItemVariable) <<
      "\"" <<
    endl;
}

void optionsMsrPitchesLanguageItem::printOptionsValues (
  ostream& os,
  int      valueFieldWidth) const
{
  os << left <<
    setw (valueFieldWidth) <<
    fVariableName <<
    " : \"" <<
    msrQuarterTonesPitchesLanguageKindAsString (
      fOptionsMsrPitchesLanguageKindItemVariable) <<
    "\"" <<
    endl;
}

ostream& operator<< (ostream& os, const S_optionsMsrPitchesLanguageItem& elt)
{
  elt->print (os);
  return os;
}

//_______________________________________________________________________________
S_msrOptions gMsrOptions;
S_msrOptions gMsrOptionsUserChoices;
S_msrOptions gMsrOptionsWithDetailedTrace;

S_msrOptions msrOptions::create (
  S_oahHandler oahHandler)
{
  msrOptions* o = new msrOptions(
    oahHandler);
  assert(o!=0);
  return o;
}

msrOptions::msrOptions (
  S_oahHandler oahHandler)
  : oahGroup (
    "MSR",
    "hmsr", "help-msr",
R"(These options control the way MSR data is handled.)",
    oahHandler)
{
  // append this options group to the options handler
  // if relevant
  if (oahHandler) {
    oahHandler->
      appendGroupToHandler (this);
  }

  // initialize it
  initializeMsrOptions (false);
}

msrOptions::~msrOptions ()
{}

#ifdef TRACE_OPTIONS
void msrOptions::initializeMsrTraceOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup traceSubGroup =
    oahSubGroup::create (
      "Trace",
      "hmsrt", "help-msr-trace",
R"()",
    oahSubGroup::kSubGroupVisibilityAlways,
    this);

  appendSubGroup (traceSubGroup);

  // MSR

  fTraceMsr          = boolOptionsInitialValue;

  traceSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "tmsr", "trace-msr",
R"(Write a trace of the LPSR graphs visiting activity to standard error.)",
        "traceMsr",
        fTraceMsr));

  // MSR visitors

  fTraceMsrVisitors  = boolOptionsInitialValue;

  traceSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "tmsrv", "trace-msr-visitors",
R"(Write a trace of the MSR graphs visiting activity to standard error.)",
        "traceMsrVisitors",
        fTraceMsrVisitors));
}
#endif

void msrOptions::initializeMsrDisplayOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup displaySubGroup =
    oahSubGroup::create (
      "Display",
      "hmsrtd", "help-msr-trace-and-display",
R"()",
    oahSubGroup::kSubGroupVisibilityAlways,
    this);

  appendSubGroup (displaySubGroup);

  // partgroups

  fDisplayPartGroups = boolOptionsInitialValue;

  displaySubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "dpg", "display-partgroups",
R"(Write the structure of the part groups to standard error.)",
        "displayPartGroups",
        fDisplayPartGroups));

  // MSR

  fDisplayMsr        = boolOptionsInitialValue;

  displaySubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "dmsr", "display-msr",
R"(Write the contents of the MSR data to standard error.)",
        "displayMsr",
        fDisplayMsr));

  // MSR details

  fDisplayMsrDetails = boolOptionsInitialValue;

  displaySubGroup->
    appendAtom (
      oahTwoBooleansAtom::create (
        "dmsrd", "display-msr-details",
R"(Write the contents of the MSR data with more details to standard error.)",
        "displayMsrDetails",
        fDisplayMsrDetails,
        fDisplayMsr));

  // MSR names

  fDisplayMsrNames   = boolOptionsInitialValue;

  displaySubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "dmnames", "display-msr-names",
R"(Only write a view of the names in the MSR to standard error.
This implies that no LilyPond code is generated.)",
        "displayMsrNames",
        fDisplayMsrNames));

  // MSR summary

  fDisplayMsrSummary = boolOptionsInitialValue;

  displaySubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "dmsum", "display-msr-summary",
R"(Only write a summary of the MSR to standard error.
This implies that no LilyPond code is generated.)",
        "displayMsrSummary",
        fDisplayMsrSummary));
}

void msrOptions::initializeMsrLanguagesOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup languagesSubGroup =
    oahSubGroup::create (
      "Languages",
      "hmsrlang", "help-msr-languages",
R"()",
    oahSubGroup::kSubGroupVisibilityAlways,
    this);

  appendSubGroup (languagesSubGroup);

  // notes pitches

  if (! setMsrQuarterTonesPitchesLanguage ("nederlands")) {
    stringstream s;

    s <<
      "INTERNAL INITIALIZATION ERROR: "
      "MSR pitches language 'nederlands' is unknown" <<
      endl <<
      "The " <<
      gQuarterTonesPitchesLanguageKindsMap.size () <<
      " known MSR pitches languages are:" <<
      endl;

    gIndenter++;

    s <<
      existingQuarterTonesPitchesLanguageKinds ();

    gIndenter--;

    optionError (s.str ());
  }

  const msrQuarterTonesPitchesLanguageKind
    msrQuarterTonesPitchesLanguageKindDefaultValue =
      kNederlands; //LilyPond default value

  languagesSubGroup->
    appendAtom (
      optionsMsrPitchesLanguageItem::create (
        "mplang", "msr-pitches-language",
        replaceSubstringInString (
          replaceSubstringInString (
            replaceSubstringInString (
R"(Use LANGUAGE to display note pitches in the MSR logs and text views.
The NUMBER LilyPond pitches languages available are:
PITCHES_LANGUAGES.
The default is 'DEFAULT_VALUE'.)",
              "NUMBER",
              to_string (gQuarterTonesPitchesLanguageKindsMap.size ())),
            "PITCHES_LANGUAGES",
            existingQuarterTonesPitchesLanguageKinds ()),
          "DEFAULT_VALUE",
          msrQuarterTonesPitchesLanguageKindAsString (
            msrQuarterTonesPitchesLanguageKindDefaultValue)),
        "LANGUAGE",
        "msrPitchesLanguage",
        fMsrQuarterTonesPitchesLanguageKind));
}

void msrOptions::initializeMsrPartsOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup partsSubGroup =
    oahSubGroup::create (
      "Parts",
      "hmsrp", "help-msr-parts",
R"()",
    oahSubGroup::kSubGroupVisibilityAlways,
    this);

  appendSubGroup (partsSubGroup);

  // MSR part rename

  partsSubGroup->
    appendAtom (
      optionsPartRenameItem::create (
        "mpr", "msr-part-rename",
        replaceSubstringInString (
R"(Rename part ORIGINAL_NAME to NEW_NAME, for example after displaying
the names in the score or a summary of the latter in a first run with options
'-dmnames, -display-msr-names' or 'dmsum, -display-msr-summary'.
PART_RENAME_SPEC can be:
'ORIGINAL_NAME = NEW_NAME'
or
"ORIGINAL_NAME = NEW_NAME"
The single or double quotes are used to allow spaces in the names
and around the '=' sign, otherwise they can be dispensed with.
Using double quotes allows for shell variables substitutions, as in:
DESSUS="Cor anglais"
EXECUTABLE -msr-part-rename "P1 = ${DESSUS}" .
There can be several occurrences of this option.)",
         "EXECUTABLE",
          gGeneralOptions->fExecutableName),
        "PART_RENAME_SPEC",
        "partRename",
        fPartsRenamingMap));

  // MSR part transpose

  partsSubGroup->
    appendAtom (
      optionsPartTransposeItem::create (
        "mpt", "msr-part-transpose",
R"(Transpose part ORIGINAL_NAME using TRANSPOSITION to tranpose in the MSR data.
PART_TRANSPOSITION_SPEC can be:
'ORIGINAL_NAME = TRANSPOSITION'
or
"ORIGINAL_NAME = TRANSPOSITION"
The single or double quotes are used to allow spaces in the names
and around the '=' sign, otherwise they can be dispensed with.
TRANSPOSITION should contain a diatonic pitch, followed if needed
by a sequence of ',' or '\'' octave indications.
Such indications cannot be mixed, and they are relative to c\', i.e. middle C.
For example, 'a', 'f' and 'bes,' can be used respectively
for instruments in 'a', 'f' and B flat respectively.
Using double quotes allows for shell variables substitutions, as in:
SAXOPHONE="bes,"
EXECUTABLE -msr-part-transpose "P1 ${SAXOPHONE}" .
There can be several occurrences of this option.)",
        "PART_TRANSPOSITION_SPEC",
        "partTranspose",
        fPartsTranspositionMap));
}

void msrOptions::initializeMsrStavesOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup stavesSubGroup =
    oahSubGroup::create (
      "Staves",
      "hmsrs", "help-msr-staves",
R"()",
    oahSubGroup::kSubGroupVisibilityAlways,
    this);

  appendSubGroup (stavesSubGroup);

  // single line staves

  fCreateVoicesStaffRelativeNumbers = boolOptionsInitialValue;

  stavesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "cslsar", "create-single-line-staves-as-rythmic",
R"(Create staves with a single line as rythmic staves.
By default, drum staves are created in this case.)",
        "createSingleLineStavesAsRythmic",
        fCreateSingleLineStavesAsRythmic));
}

void msrOptions::initializeMsrVoicesOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup voicesSubGroup =
    oahSubGroup::create (
      "Voices",
      "hmsrv", "help-msr-voices",
R"()",
    oahSubGroup::kSubGroupVisibilityAlways,
    this);

  appendSubGroup (voicesSubGroup);

  // staff relative numbers

  fCreateVoicesStaffRelativeNumbers = boolOptionsInitialValue;

  voicesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "cvsrvn", "create-voices-staff-relative-numbers",
R"(Generate voices names with numbers relative to their staff.
By default, the voice numbers found are used,
which may be global to the score.)",
        "createVoicesStaffRelativeNumbers",
        fCreateVoicesStaffRelativeNumbers));
}

void msrOptions::initializeMsrRepeatsOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup repeatsSubGroup =
    oahSubGroup::create (
      "Repeats",
      "hmsrr", "help-msr-repeats",
R"()",
    oahSubGroup::kSubGroupVisibilityAlways,
    this);

  appendSubGroup (repeatsSubGroup);

  // barlines

  fCreateImplicitInitialRepeatBarline = boolOptionsInitialValue;

  repeatsSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "ciirb", "create-implicit-initial-repeat-barline",
R"(Create an implicit repeat barline at the beginning of the stave
in case there is none, as is usual in scores.
By default, no such barline is added.)",
        "createImplicitInitialRepeatBarline",
        fCreateImplicitInitialRepeatBarline));
}

void msrOptions::initializeMsrNotesOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup notesSubGroup =
    oahSubGroup::create (
      "Notes",
      "hmsrn", "help-msr-notes",
R"()",
    oahSubGroup::kSubGroupVisibilityAlways,
    this);

  appendSubGroup (notesSubGroup);

  // delay rests dynamics

  fDelayRestsDynamics = false;

  notesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "drdyns", "delay-rests-dynamics",
R"()",
        "delayRestsDynamics",
        fDelayRestsDynamics));

  // delay rests words

  fDelayRestsWords = false;

  notesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "drwords", "delay-rests-words",
R"()",
        "delayRestsWords",
        fDelayRestsWords));

  // delay rests beams

  fDelayRestsBeams = false;

  notesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "drbeams", "delay-rests-beams",
R"()",
        "delayRestsBeams",
        fDelayRestsBeams));

  // delay rests slurs

  fDelayRestsSlurs = false;

  notesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "drslurs", "delay-rests-slurs",
R"()",
        "delayRestsSlurs",
        fDelayRestsSlurs));

  // delay rests ligatures

  fDelayRestsLigatures = false;

  notesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "drligs", "delay-rests-ligatures",
R"(<bracket/> in MusicXML, '\[... \}' in LilyPond)",
        "delayRestsLigatures",
        fDelayRestsLigatures));

  // delay rests pedals

  fDelayRestsPedals = false;

  notesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "drpeds", "delay-rests-pedals",
R"()",
        "delayRestsPedals",
        fDelayRestsPedals));

  // delay rests slashes

  fDelayRestsSlashes = false;

  notesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "drslashes", "delay-rests-slashes",
R"('<slash/>' in MusicXML)",
        "delayRestsSlashes",
        fDelayRestsSlashes));

  // delay rests wedges

  fDelayRestsWedges = false;

  notesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "drwedges", "delay-rests-wedges",
R"('<wedge/>' in MusicXML, '<!' in LilyPond)",
        "delayRestsWedges",
        fDelayRestsWedges));
}

void msrOptions::initializeMsrLyricsOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup lyricsSubGroup =
    oahSubGroup::create (
      "Lyrics",
      "hmsrlyrd", "help-msr-lyrics",
R"()",
    oahSubGroup::kSubGroupVisibilityAlways,
    this);

  appendSubGroup (lyricsSubGroup);

  // stanzas numbers

  fAddStanzasNumbers  = false;

  lyricsSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "asn", "add-stanzas-numbers",
R"(Add stanzas numbers to lyrics.)",
        "addStanzasNumbers",
        fAddStanzasNumbers));
}

void msrOptions::initializeMsrHarmoniesOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup harmoniesSubGroup =
    oahSubGroup::create (
      "Harmonies",
      "hmsrh", "help-msr-harmonies",
R"()",
    oahSubGroup::kSubGroupVisibilityAlways,
    this);

  appendSubGroup (harmoniesSubGroup);

  // show harmony voices

  fShowHarmonyVoices      = boolOptionsInitialValue;

  harmoniesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "shv", "show-harmony-voices",
R"(Show the parts harmony voices in the MSR data
even though it does not contain music.)",
        "showHarmonyVoices",
        fShowHarmonyVoices));
}

void msrOptions::initializeMsrFiguredBassOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup figuredBassSubGroup =
    oahSubGroup::create (
      "Figured bass",
      "hmsrfb", "help-msr-figured-bass",
R"()",
    oahSubGroup::kSubGroupVisibilityAlways,
    this);

  appendSubGroup (figuredBassSubGroup);

  // show figured bass voices

  fShowFiguredBassVoices      = boolOptionsInitialValue;

  figuredBassSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "sfbv", "show-figured-bass-voices",
R"(Show the figured bass harmony voices in the MSR data
even though they do not contain music.)",
        "showFiguredBassVoices",
        fShowFiguredBassVoices));
}

void msrOptions::initializeMsrExitAfterSomePassesOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup
    exitAfterSomePassesSubGroup =
      oahSubGroup::create (
        "Exit after some passes",
        "hme", "help-msr-exit",
R"()",
      oahSubGroup::kSubGroupVisibilityAlways,
      this);

  appendSubGroup (exitAfterSomePassesSubGroup);

  // exit after pass 2a

  fExit2a = boolOptionsInitialValue;

  S_oahBooleanAtom
    exit2aOptionsBooleanItem =
      oahBooleanAtom::create (
        "e2a", "exit-2a",
R"(Exit after pass 2a, i.e. after conversion
of the MusicXML tree to an MSR skeleton.)",
        "exit2a",
        fExit2a);
        /* JMI
  // '-exit-2a' is hidden...
  exit2aOptionsBooleanItem->
    setOptionsElementIsHidden ();
    */

  exitAfterSomePassesSubGroup->
    appendAtom (
      exit2aOptionsBooleanItem);

  // exit after pass 2b

  fExit2b = boolOptionsInitialValue;

  S_oahBooleanAtom
    exit2bOptionsBooleanItem =
      oahBooleanAtom::create (
        "e2b", "exit-2b",
R"(Exit after pass 2b, i.e. after conversion
of the MusicXML tree to MSR.)",
        "exit2b",
        fExit2b);
        /* JMI
  // '-exit-2b' is hidden...
  exit2bOptionsBooleanItem->
    setOptionsElementIsHidden ();
    */

  exitAfterSomePassesSubGroup->
    appendAtom (
      exit2bOptionsBooleanItem);
}

void msrOptions::initializeMsrOptions (
  bool boolOptionsInitialValue)
{
#ifdef TRACE_OPTIONS
  // trace
  // --------------------------------------
  initializeMsrTraceOptions (
    boolOptionsInitialValue);
#endif

  // display
  // --------------------------------------
  initializeMsrDisplayOptions (
    boolOptionsInitialValue);

  // languages
  // --------------------------------------
  initializeMsrLanguagesOptions (
    boolOptionsInitialValue);

  // parts
  // --------------------------------------
  initializeMsrPartsOptions (
    boolOptionsInitialValue);

  // staves
  // --------------------------------------
  initializeMsrStavesOptions (
    boolOptionsInitialValue);

  // voices
  // --------------------------------------
  initializeMsrVoicesOptions (
    boolOptionsInitialValue);

  // repeats
  // --------------------------------------
  initializeMsrRepeatsOptions (
    boolOptionsInitialValue);

  // notes
  // --------------------------------------
  initializeMsrNotesOptions (
    boolOptionsInitialValue);

  // lyrics
  // --------------------------------------
  initializeMsrLyricsOptions (
    boolOptionsInitialValue);

  // harmonies
  // --------------------------------------
  initializeMsrHarmoniesOptions (
    boolOptionsInitialValue);

  // figured bass
  // --------------------------------------
  initializeMsrFiguredBassOptions (
    boolOptionsInitialValue);

  // exit after some passes
  // --------------------------------------
  initializeMsrExitAfterSomePassesOptions (
    boolOptionsInitialValue);
}

S_msrOptions msrOptions::createCloneWithDetailedTrace ()
{
  S_msrOptions
    clone =
      msrOptions::create (0);
      // 0 not to have it inserted twice in the option handler

  // set the options handler upLink
  clone->
    setOptionsHandlerUpLink (
      fHandlerUpLink);


  // trace and display
  // --------------------------------------

  clone->fTraceMsr =
    true;

  clone->fTraceMsrVisitors =
    true;

  clone->fDisplayPartGroups =
    true;

  clone->fDisplayMsr =
    fDisplayMsr;
  clone->fDisplayMsrDetails =
    fDisplayMsrDetails;

  clone->fDisplayMsrNames =
    fDisplayMsrNames;
  clone->fDisplayMsrSummary =
    fDisplayMsrSummary;


  // languages
  // --------------------------------------

  clone->fMsrQuarterTonesPitchesLanguageKind =
    fMsrQuarterTonesPitchesLanguageKind;


  // parts
  // --------------------------------------

  clone->fPartsRenamingMap =
    fPartsRenamingMap;
  clone->fPartsTranspositionMap =
    fPartsTranspositionMap;


  // staves
  // --------------------------------------

  clone->fCreateSingleLineStavesAsRythmic =
    fCreateSingleLineStavesAsRythmic;


  // voices
  // --------------------------------------

  clone->fCreateVoicesStaffRelativeNumbers =
    fCreateVoicesStaffRelativeNumbers;


  // repeats
  // --------------------------------------

  clone->fCreateImplicitInitialRepeatBarline =
    fCreateImplicitInitialRepeatBarline;


  // notes
  // --------------------------------------

  clone->fDelayRestsDynamics =
    fDelayRestsDynamics;
  clone->fDelayRestsWords =
    fDelayRestsWords;
  clone->fDelayRestsSlurs =
    fDelayRestsSlurs;
  clone->fDelayRestsLigatures =
    fDelayRestsLigatures;
  clone->fDelayRestsPedals =
    fDelayRestsPedals;
  clone->fDelayRestsSlashes =
    fDelayRestsSlashes;
  clone->fDelayRestsWedges =
    fDelayRestsWedges;


  // lyrics
  // --------------------------------------

  clone->fAddStanzasNumbers =
    fAddStanzasNumbers;

  // harmonies
  // --------------------------------------

  clone->fShowHarmonyVoices =
    fShowHarmonyVoices;


  // figured bass
  // --------------------------------------

  clone->fShowFiguredBassVoices =
    fShowFiguredBassVoices;

  return clone;
}

//______________________________________________________________________________
bool msrOptions::setMsrQuarterTonesPitchesLanguage (string language)
{
  // is language in the pitches languages map?
  map<string, msrQuarterTonesPitchesLanguageKind>::const_iterator
    it =
      gQuarterTonesPitchesLanguageKindsMap.find (language);

  if (it == gQuarterTonesPitchesLanguageKindsMap.end ()) {
    // no, language is unknown in the map
    return false;
  }

  fMsrQuarterTonesPitchesLanguageKind = (*it).second;

  return true;
}

//______________________________________________________________________________
void msrOptions::enforceQuietness ()
{
  fTraceMsr = false;
  fTraceMsrVisitors = false;
  fDisplayPartGroups = false;
  fDisplayMsr = false;
  fDisplayMsrDetails = false;
  fDisplayMsrNames = false;
  fDisplayMsrSummary = false;
}

//______________________________________________________________________________
void msrOptions::checkOptionsConsistency ()
{
  // JMI
}

//______________________________________________________________________________
void msrOptions::printMsrOptionsValues (int fieldWidth)
{
  gLogIOstream <<
    "The MSR options are:" <<
    endl;

  gIndenter++;


  // trace and display
  // --------------------------------------

  gLogIOstream <<
    "Trace and display:" <<
    endl;

  gIndenter++;

  gLogIOstream << left <<
    setw (fieldWidth) << "traceMsr" << " : " <<
    booleanAsString (fTraceMsr) <<
    endl <<

    setw (fieldWidth) << "traceMsrVisitors" << " : " <<
    booleanAsString (fTraceMsrVisitors) <<
    endl <<

    setw (fieldWidth) << "displayPartGroups" << " : " <<
    booleanAsString (fDisplayPartGroups) <<
    endl <<

    setw (fieldWidth) << "displayMsr" << " : " <<
    booleanAsString (fDisplayMsr) <<
    endl <<
    setw (fieldWidth) << "displayMsrDetails" << " : " <<
    booleanAsString (fDisplayMsrDetails) <<
    endl <<

    setw (fieldWidth) << "displayMsrNames" << " : " <<
    booleanAsString (fDisplayMsrNames) <<
    endl <<

    setw (fieldWidth) << "displayMsrSummary" << " : " <<
    booleanAsString (fDisplayMsrSummary) <<
    endl;

  gIndenter--;


  // languages
  // --------------------------------------

  gLogIOstream <<
     "Languages:" <<
    endl;

  gIndenter++;

  gLogIOstream << left <<
    setw (fieldWidth) << "msrPitchesLanguage" << " : \"" <<
    msrQuarterTonesPitchesLanguageKindAsString (
      fMsrQuarterTonesPitchesLanguageKind) <<
      "\"" <<
    endl;

  gIndenter--;


  // parts
  // --------------------------------------

  gLogIOstream <<
     "Parts:" <<
    endl;

  gIndenter++;

  gLogIOstream << left <<
    setw (fieldWidth) << "parts renaming" << " : ";

  if (! fPartsRenamingMap.size ()) {
    gLogIOstream <<
      "none";
  }

  else {
    for (
      map<string, string>::const_iterator i =
        fPartsRenamingMap.begin ();
      i != fPartsRenamingMap.end ();
      i++
  ) {
        gLogIOstream <<
          "\"" << ((*i).first) << "\" -> \"" << ((*i).second) << "\"";
    } // for
  }

  gLogIOstream << endl;

  gLogIOstream << left <<
    setw (fieldWidth) << "parts transposition" << " : ";

  if (! fPartsTranspositionMap.size ()) {
    gLogIOstream <<
      "none";
  }

  else {
    for (
      map<string, S_msrSemiTonesPitchAndOctave>::const_iterator i =
        fPartsTranspositionMap.begin ();
      i != fPartsTranspositionMap.end ();
      i++
  ) {
        gLogIOstream <<
          "\"" << ((*i).first) << " = " << ((*i).second) << "\" ";
    } // for
  }

  gLogIOstream << endl;

  gIndenter--;


  // staves
  // --------------------------------------

  gLogIOstream <<
    "Staves:" <<
    endl;

  gIndenter++;

  gLogIOstream << left <<
    setw (fieldWidth) <<
    "createSingleLineStavesAsRythmic" << " : " <<
    booleanAsString (fCreateSingleLineStavesAsRythmic) <<
    endl;

  gIndenter--;


  // voices
  // --------------------------------------

  gLogIOstream <<
    "Voices:" <<
    endl;

  gIndenter++;

  gLogIOstream << left <<
    setw (fieldWidth) <<
    "createVoicesStaffRelativeNumbers" << " : " <<
    booleanAsString (fCreateVoicesStaffRelativeNumbers) <<
    endl;

  gIndenter--;


  // repeats
  // --------------------------------------

  gLogIOstream <<
    "Repeats:" <<
    endl;

  gIndenter++;

  gLogIOstream << left <<
    setw (fieldWidth) <<
    "createImplicitInitialRepeatBarline" << " : " <<
    booleanAsString (fCreateImplicitInitialRepeatBarline) <<
    endl;

  gIndenter--;


  // notes
  // --------------------------------------

  gLogIOstream <<
     "Notes:" <<
    endl;

  gIndenter++;

  gLogIOstream << left <<
    setw (fieldWidth) << "delayRestsDynamics" << " : " <<
    booleanAsString (fDelayRestsDynamics) <<
    endl <<

    setw (fieldWidth) << "delayRestsWords" << " : " <<
    booleanAsString (fDelayRestsWords) <<
    endl <<

    setw (fieldWidth) << "delayRestsSlurs" << " : " <<
    booleanAsString (fDelayRestsSlurs) <<
    endl <<

    setw (fieldWidth) << "delayRestsLigatures" << " : " <<
    booleanAsString (fDelayRestsLigatures) <<
    endl <<

    setw (fieldWidth) << "delayRestsPedals" << " : " <<
    booleanAsString (fDelayRestsPedals) <<
    endl <<

    setw (fieldWidth) << "delayRestsSlashes" << " : " <<
    booleanAsString (fDelayRestsSlashes) <<
    endl <<

    setw (fieldWidth) << "delayRestsWedges" << " : " <<
    booleanAsString (fDelayRestsWedges) <<
    endl;

  gIndenter--;


  // lyrics
  // --------------------------------------

  gLogIOstream <<
    "Lyrics:" <<
    endl;

  gIndenter++;

  gLogIOstream <<
    setw (fieldWidth) << "addStanzasNumbers" << " : " <<
    booleanAsString (fAddStanzasNumbers) <<
    endl;

  gIndenter--;


  // harmonies
  // --------------------------------------

  gLogIOstream <<
    "Harmonies:" <<
    endl;

  gIndenter++;

  gLogIOstream << left <<
    setw (fieldWidth) << "showHarmonyVoices" << " : " <<
    booleanAsString (fShowHarmonyVoices) <<
    endl;

  gIndenter--;


  // figured bass
  // --------------------------------------

  gLogIOstream <<
    "Figured bass:" <<
    endl;

  gIndenter++;

  gLogIOstream << left <<
    setw (fieldWidth) << "showFiguredBassVoices" << " : " <<
    booleanAsString (fShowFiguredBassVoices) <<
    endl;

  gIndenter--;

  gIndenter--;


  // exit after some passes
  // --------------------------------------

  gLogIOstream <<
    "Exit after some passes:" <<
    endl;

  gIndenter++;

  gLogIOstream << left <<
    setw (fieldWidth) << "exit2a" << " : " <<
    booleanAsString (fExit2a) <<
    endl <<
    setw (fieldWidth) << "exit2b" << " : " <<
    booleanAsString (fExit2b) <<
    endl;

  gIndenter--;
}

S_oahValuedAtom msrOptions::handleOptionsItem (
  ostream&      os,
  S_oahAtom item)
{
  S_oahValuedAtom result;

  if (
    // part rename item?
    S_optionsPartRenameItem
      partRenameItem =
        dynamic_cast<optionsPartRenameItem*>(&(*item))
    ) {
#ifdef TRACE_OPTIONS
    if (gTraceOptions->fTraceOptions) {
      os <<
        "==> oahAtom is of type 'optionsPartRenameItem'" <<
        endl;
    }
#endif

    // wait until the value is met
    result = partRenameItem;
  }

  else if (
    // part transpose item?
    S_optionsPartTransposeItem
      partTransposeItem =
        dynamic_cast<optionsPartTransposeItem*>(&(*item))
    ) {
#ifdef TRACE_OPTIONS
    if (gTraceOptions->fTraceOptions) {
      os <<
        "==> oahAtom is of type 'optionsPartTransposeItem'" <<
        endl;
    }
#endif

    // wait until the value is met
    result = partTransposeItem;
  }

  else if (
    // pitches language item?
    S_optionsMsrPitchesLanguageItem
      pitchesLanguageItem =
        dynamic_cast<optionsMsrPitchesLanguageItem*>(&(*item))
    ) {
#ifdef TRACE_OPTIONS
    if (gTraceOptions->fTraceOptions) {
      os <<
        "==> oahAtom is of type 'optionsMsrPitchesLanguageItem'" <<
        endl;
    }
#endif

    // wait until the value is met
    result = pitchesLanguageItem;
  }

  return result;
}

void msrOptions::handleOptionsPartRenameItemValue (
  ostream&                os,
  S_optionsPartRenameItem partRenameItem,
  string                  theString)
{
  // theString contains the part rename specification
  // decipher it to extract the old and new part names

#ifdef TRACE_OPTIONS
  if (gTraceOptions->fTraceOptions) {
    os <<
      "==> oahAtom is of type 'optionsPartRenameItem'" <<
      endl;
  }
#endif

  string regularExpression (
    "[[:space:]]*([^[:space:]]*)[[:space:]]*"
    "="
    "[[:space:]]*([^[:space:]]*)[[:space:]]*");

  regex  e (regularExpression);
  smatch sm;

  regex_match (theString, sm, e);

  unsigned smSize = sm.size ();

#ifdef TRACE_OPTIONS
  if (gTraceOptions->fTraceOptions) {
    os <<
      "There are " << smSize << " matches" <<
      " for part rename string '" << theString <<
      "' with regex '" << regularExpression <<
      "'" <<
      endl;
  }
#endif

  if (smSize) {
#ifdef TRACE_OPTIONS
    if (gTraceOptions->fTraceOptions) {
      for (unsigned i = 0; i < smSize; ++i) {
        os <<
          "[" << sm [i] << "] ";
      } // for
      os << endl;
    }
#endif
  }

  else {
    stringstream s;

    s <<
      "-msrPartRename argument '" << theString <<
      "' is ill-formed";

    optionError (s.str ());

    printSpecificSubGroupHelp (
      os,
      partRenameItem->
        getSubGroupUpLink ());

    exit (4);
  }

  string
    oldPartName = sm [1],
    newPartName = sm [2];

#ifdef TRACE_OPTIONS
  if (gTraceOptions->fTraceOptions) {
    os <<
      "--> oldPartName = \"" << oldPartName << "\", " <<
      "--> newPartName = \"" << newPartName << "\"" <<
      endl;
  }
#endif

  map<string, string>
    partRenameItemVariable =
      partRenameItem->
        getOptionsPartRenameItemVariable ();

  // is this part name in the part renaming map?
  map<string, string>::iterator
    it =
      partRenameItemVariable.find (oldPartName);

  if (it != partRenameItemVariable.end ()) {
    // yes, issue error message
    stringstream s;

    s <<
      "Part \"" << oldPartName << "\" occurs more that one" <<
      "in the '--partName' option";

    optionError (s.str ());
    exit (4);
  }

  else {
    partRenameItem->
      setPartRenameItemVariableValue (
        oldPartName, newPartName);
  }
}

void msrOptions::handleOptionsPartTransposeItemValue (
  ostream&                   os,
  S_optionsPartTransposeItem partTransposeItem,
  string                     theString)
{
  // theString contains the part transpose specification
  // decipher it to extract the old and new part names

#ifdef TRACE_OPTIONS
  if (gTraceOptions->fTraceOptions) {
    os <<
      "==> oahAtom is of type 'S_optionsPartTransposeItem'" <<
      endl;
  }
#endif

/* JMI
  string regularExpression (
    "[[:space:]]*(.*)[[:space:]]*"
    "="
    "[[:space:]]*(.*)[[:space:]]*");

  regex  e (regularExpression);
  smatch sm;

  regex_match (theString, sm, e);

  unsigned smSize = sm.size ();

#ifdef TRACE_OPTIONS
  if (gTraceOptions->fTraceOptions) {
    os <<
      "There are " << smSize << " matches" <<
      " for part transpose string '" << theString <<
      "' with regex '" << regularExpression <<
      "'" <<
      endl;
  }
#endif

  if (smSize) {
#ifdef TRACE_OPTIONS
    if (gTraceOptions->fTraceOptions) {
      for (unsigned i = 0; i < smSize; ++i) {
        os <<
          "[" << sm [i] << "] ";
      } // for
      os << endl;
    }
#endif
  }

  else {
    stringstream s;

    s <<
      "-msrPartTranspose argument '" << theString <<
      "' is ill-formed";

    optionError (s.str ());

    printSpecificSubGroupHelp (
      os,
      partTransposeItem->
        getSubGroupUpLink ());

    exit (4);
  }

  string
    oldPartName = sm [1],
    newPartName = sm [2];

#ifdef TRACE_OPTIONS
  if (gTraceOptions->fTraceOptions) {
    os <<
      "--> oldPartName = \"" << oldPartName << "\", " <<
      "--> newPartName = \"" << newPartName << "\"" <<
      endl;
  }
#endif

  map<string, string>
    partTransposeItemVariable =
      partTransposeItem->
        getOptionsPartTransposeItemVariable ();

  // is this part name in the part renaming map?
  map<string, string>::iterator
    it =
      partTransposeItemVariable.find (oldPartName);

  if (it != partTransposeItemVariable.end ()) {
    // yes, issue error message
    stringstream s;

    s <<
      "Part \"" << oldPartName << "\" occurs more that one" <<
      "in the '--partName' option";

    optionError (s.str ());
    exit (4);
  }

  else {
    partTransposeItem->
      setPartTransposeItemVariableValue (
        oldPartName, newPartName);
  }
  */
}

void msrOptions::handleOptionsMsrPitchesLanguageItemValue (
  ostream&                        os,
  S_optionsMsrPitchesLanguageItem pitchesLanguageKindItem,
  string                          theString)
{
  // theString contains the language name:
  // is it in the pitches languages map?

#ifdef TRACE_OPTIONS
  if (gTraceOptions->fTraceOptions) {
    os <<
      "==> oahAtom is of type 'optionsMsrPitchesLanguageItem'" <<
      endl;
  }
#endif

  map<string, msrQuarterTonesPitchesLanguageKind>::const_iterator
    it =
      gQuarterTonesPitchesLanguageKindsMap.find (
        theString);

  if (it == gQuarterTonesPitchesLanguageKindsMap.end ()) {
    // no, language is unknown in the map

    printOptionsSummary (os);

    stringstream s;

    s <<
      "MSR pitches language '" << theString <<
      "' is unknown" <<
      endl <<
      "The " <<
      gQuarterTonesPitchesLanguageKindsMap.size () <<
      " known MSR pitches languages are:" <<
      endl;

    gIndenter++;

    s <<
      existingQuarterTonesPitchesLanguageKinds ();

    gIndenter--;

    optionError (s.str ());

//     exit (4); // JMI
    abort ();
  }

  pitchesLanguageKindItem->
    setPitchesLanguageKindItemVariableValue (
      (*it).second);
}

void msrOptions::handleOptionsItemValue (
  ostream&      os,
  S_oahAtom item,
  string        theString)
{
  if (
    // part rename item?
    S_optionsPartRenameItem
      partRenameItem =
        dynamic_cast<optionsPartRenameItem*>(&(*item))
  ) {
    handleOptionsPartRenameItemValue (
      os,
      partRenameItem,
      theString);
  }

  else if (
    // part transpose item?
    S_optionsPartTransposeItem
      partTransposeItem =
        dynamic_cast<optionsPartTransposeItem*>(&(*item))
  ) {
    handleOptionsPartTransposeItemValue (
      os,
      partTransposeItem,
      theString);
  }

  else if (
    // MSR pitches language item?
    S_optionsMsrPitchesLanguageItem
      pitchesLanguageKindItem =
        dynamic_cast<optionsMsrPitchesLanguageItem*>(&(*item))
    ) {
    handleOptionsMsrPitchesLanguageItemValue (
      os,
      pitchesLanguageKindItem,
      theString);
  }
}

ostream& operator<< (ostream& os, const S_msrOptions& elt)
{
  elt->print (os);
  return os;
}

//______________________________________________________________________________
void initializeMsrOptionsHandling (
  S_oahHandler oahHandler)
{
#ifdef TRACE_OPTIONS
  if (gTraceOptions->fTraceOptions && ! gGeneralOptions->fQuiet) {
    gLogIOstream <<
      "Initializing MSR options handling" <<
      endl;
  }
#endif

  // MSR options
  // ------------------------------------------------------

  gMsrOptionsUserChoices = msrOptions::create (
    oahHandler);
  assert(gMsrOptionsUserChoices != 0);

  gMsrOptions =
    gMsrOptionsUserChoices;

  // prepare for measure detailed trace
  // ------------------------------------------------------

  gMsrOptionsWithDetailedTrace =
    gMsrOptions->
      createCloneWithDetailedTrace ();
}


}

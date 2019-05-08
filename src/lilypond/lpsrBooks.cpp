/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#include "lpsrBooks.h"

#include "version.h"

#include "generalOptions.h"

#include "setTraceOptionsIfDesired.h"
#ifdef TRACE_OPTIONS
  #include "traceOptions.h"
#endif


using namespace std;

namespace MusicXML2
{

//______________________________________________________________________________
S_lpsrBookPartBlock lpsrBookPartBlock::create (
  int            inputLineNumber)
{
  lpsrBookPartBlock* o = new lpsrBookPartBlock (
    inputLineNumber);
  assert(o!=0);
  return o;
}

lpsrBookPartBlock::lpsrBookPartBlock (
  int            inputLineNumber)
    : lpsrElement (inputLineNumber)
{
  // create the score command parallel music
  fScoreBlockParallelMusicBLock =
    lpsrParallelMusicBLock::create (
      inputLineNumber,
      lpsrParallelMusicBLock::kEndOfLine);

  // create the score command layout
  fScoreBlockLayout =
    lpsrLayout::create (
      inputLineNumber);

  // create the score command midi
  string midiTempoDuration  = gLilypondOptions->fMidiTempo.first;
  int    midiTempoPerSecond = gLilypondOptions->fMidiTempo.second;

  fScoreBlockMidi =
    msrMidi::create (
      inputLineNumber,
      midiTempoDuration,
      midiTempoPerSecond);
}

lpsrBookPartBlock::~lpsrBookPartBlock ()
{}

void lpsrBookPartBlock::appendPartGroupBlockToScoreBlock (
  S_lpsrPartGroupBlock partGroupBlock)
{
#ifdef TRACE_OPTIONS
  if (gTraceOptions->fTracePartGroups) {
    gLogIOstream <<
      "Appending part group block " <<
       partGroupBlock-> getPartGroup ()-> getPartGroupCombinedName () <<
       " to LPSR score" <<
       endl;
  }
#endif

  fScoreBlockParallelMusicBLock->
    appendPartGroupBlockToParallelMusicBLock (
      partGroupBlock);

//               fScoreBlockElements.push_back(partGroupBlock);
}

/* JMI
void lpsrBookPartBlock::appendVoiceUseToParallelMusicBLock (
  S_lpsrUseVoiceCommand voiceUse)
{
#ifdef TRACE_OPTIONS
  if (gTraceOptions->fTraceVoices) {
    gLogIOstream <<
      "Appending the use of voice \"" <<
       voiceUse-> getVoice ()-> getVoiceName () <<
       "\" to LPSR score" <<
       endl;
  }
#endif

  fScoreBlockParallelMusicBLock->
    addElementToParallelMusicBLock (voiceUse);

//     JMI             fScoreBlockElements.push_back(voiceUse);
}

void lpsrBookPartBlock::appendLyricsUseToParallelMusicBLock (
  S_lpsrNewLyricsBlock lyricsUse)
{
#ifdef TRACE_OPTIONS
  if (gTraceOptions->fTraceLyrics) {
    gLogIOstream <<
      "Appending the use of stanza " <<
       lyricsUse-> getStanza ()-> getStanzaName () <<
       " to LPSR score" <<
       endl;
  }
#endif

  fScoreBlockParallelMusicBLock->
    addElementToParallelMusicBLock (lyricsUse);
}
*/

void lpsrBookPartBlock::acceptIn (basevisitor* v)
{
  if (gLpsrOptions->fTraceLpsrVisitors) {
    gLogIOstream <<
      "% ==> lpsrBookPartBlock::acceptIn ()" <<
      endl;
  }

  if (visitor<S_lpsrBookPartBlock>*
    p =
      dynamic_cast<visitor<S_lpsrBookPartBlock>*> (v)) {
        S_lpsrBookPartBlock elem = this;

        if (gLpsrOptions->fTraceLpsrVisitors) {
          gLogIOstream <<
            "% ==> Launching lpsrBookPartBlock::visitStart ()" <<
            endl;
        }
        p->visitStart (elem);
  }
}

void lpsrBookPartBlock::acceptOut (basevisitor* v)
{
  if (gLpsrOptions->fTraceLpsrVisitors) {
    gLogIOstream <<
      "% ==> lpsrBookPartBlock::acceptOut ()" <<
      endl;
  }

  if (visitor<S_lpsrBookPartBlock>*
    p =
      dynamic_cast<visitor<S_lpsrBookPartBlock>*> (v)) {
        S_lpsrBookPartBlock elem = this;

        if (gLpsrOptions->fTraceLpsrVisitors) {
          gLogIOstream <<
            "% ==> Launching lpsrBookPartBlock::visitEnd ()" <<
            endl;
        }
        p->visitEnd (elem);
  }
}

void lpsrBookPartBlock::browseData (basevisitor* v)
{
  if (gLpsrOptions->fTraceLpsrVisitors) {
    gLogIOstream <<
      "% ==> lpsrBookPartBlock::browseData ()" <<
      endl;
  }

  {
    // browse the score command parallel music
    msrBrowser<lpsrParallelMusicBLock> browser (v);
    browser.browse (*fScoreBlockParallelMusicBLock);
  }

/* JMI
  for (
    vector<S_msrElement>::const_iterator i = fScoreBlockElements.begin ();
    i != fScoreBlockElements.end ();
    i++) {
    // browse the element
 //   msrBrowser<msrElement> browser (v);
 //   browser.browse (*(*i));
  } // for
*/
  {
    // browse the score command layout
    msrBrowser<lpsrLayout> browser (v);
    browser.browse (*fScoreBlockLayout);
  }

  {
    // browse the score command midi
    msrBrowser<msrMidi> browser (v);
    browser.browse (*fScoreBlockMidi);
  }

  if (gLpsrOptions->fTraceLpsrVisitors) {
    gLogIOstream <<
      "% <== lpsrBookPartBlock::browseData ()" <<
      endl;
  }
}

void lpsrBookPartBlock::print (ostream& os)
{
  os << "ScoreBlock" << endl << endl;

  gIndenter++;

  os <<
    fScoreBlockParallelMusicBLock <<
    endl;

  os <<
    fScoreBlockLayout <<
    endl;

  os <<
    fScoreBlockMidi <<
    endl;

  gIndenter--;
}

ostream& operator<< (ostream& os, const S_lpsrBookPartBlock& scr)
{
  scr->print (os);
  return os;
}

//______________________________________________________________________________
S_lpsrBookPart lpsrBookPart::create (
  int            inputLineNumber,
  S_msrScore     mScore)
{
  lpsrBookPart* o = new lpsrBookPart (
    inputLineNumber, mScore);
  assert(o!=0);
  return o;
}

lpsrBookPart::lpsrBookPart (
  int            inputLineNumber,
  S_msrScore     mScore)
    : lpsrElement (inputLineNumber)
{
  fMsrScore = mScore;

  // create the LilyPond version assoc
  fLilypondVersion =
    lpsrVarValAssoc::create (
      inputLineNumber,
      lpsrVarValAssoc::kCommentedNo,
      lpsrVarValAssoc::kWithBackSlashYes,
      lpsrVarValAssoc::kLibraryVersion,
      lpsrVarValAssoc::kVarValSeparatorSpace,
      lpsrVarValAssoc::kQuotesAroundValueYes,
      "2.20.0",
      lpsrVarValAssoc::g_LilyPondVarValAssocNoUnit,
      kFontStyleNone,
      kFontWeightNone,
      lpsrVarValAssoc::g_LilyPondVarValAssocNoComment,
      lpsrVarValAssoc::kEndlOnce);

  // should the initial comments about xml2ly and the options used
  // be generated?
  if (gLilypondOptions->fXml2lyInfos) {
    // create the input source name comment
    {
      stringstream s;

      s <<
        "Generated by xml2ly " << currentVersionNumber () <<
        " from ";

      if (gGeneralOptions->fInputSourceName == "-") {
        s << "standard input";
      }
      else {
        s << "\"" << gGeneralOptions->fInputSourceName << "\"";
      }

      s <<
        endl <<
        "% on " << gGeneralOptions->fTranslationDate <<
        endl;

      fInputSourceNameComment =
        lpsrComment::create (
          inputLineNumber,
          s.str (),
          lpsrComment::kNoGapAfterwards);
    }

    // create the translation date comment
    {
      stringstream s;

      s <<
        "% Translation command was:";

      fTranslationDateComment =
        lpsrComment::create (
          inputLineNumber,
          s.str (),
          lpsrComment::kNoGapAfterwards);
    }

    // do the command line long and short options differ?
    bool
      longAndShortOptionsDiffer =
      gGeneralOptions->fCommandLineWithShortOptions
        !=
      gGeneralOptions->fCommandLineWithLongOptions;


  // create the command line long options comment
  {
    stringstream s;

    s <<
      gTab <<
      gGeneralOptions->fCommandLineWithLongOptions;

    if (longAndShortOptionsDiffer) {
      s <<
        endl <<
        "% or:";
    }

    fCommandLineLongOptionsComment =
      lpsrComment::create (
        inputLineNumber,
        s.str (),
        longAndShortOptionsDiffer
          ? lpsrComment::kNoGapAfterwards
          : lpsrComment::kGapAfterwards);
  }

  if (longAndShortOptionsDiffer) {
    // create the command line short options comment
    stringstream s;

    s <<
      gTab <<
      gGeneralOptions->fCommandLineWithShortOptions;

    fCommandLineShortOptionsComment =
      lpsrComment::create (
        inputLineNumber,
        s.str (),
        lpsrComment::kGapAfterwards);
  }
}

  // create the global staff size assoc
  fGlobalStaffSizeAssoc =
    lpsrSchemeVariable::create (
      inputLineNumber,
      lpsrSchemeVariable::kCommentedNo,
      "set-global-staff-size",
      "20", // the LilyPond default
      "Comment or adapt next line as needed (default is 20)",
      lpsrSchemeVariable::kEndlTwice);

  // initialize Scheme functions informations
  fTongueSchemeFunctionIsNeeded              = false;
  fCustomShortBarLineSchemeFunctionIsNeeded  = false;
  fEditorialAccidentalSchemeFunctionIsNeeded = false;

  if (gLilypondOptions->fLilypondCompileDate) {
    // create the date and time functions
    addDateAndTimeSchemeFunctionsToScore ();
  }

  if (gLilypondOptions->fPointAndClickOff) {
    // create the pointAndClickOff command
    addPointAndClickOffSchemeFunctionsToScore ();
  }

  if (gLilypondOptions->fPointAndClickOff) {
    // create the glissandoWithText command
    addGlissandoWithTextSchemeFunctionsToScore ();
  }

  if (gLilypondOptions->fJianpu) {
    // create the Jianpu include command JMI
  }

  // create the header
  fHeader =
    lpsrHeader::create (
      inputLineNumber);

  // create the paper
  fPaper =
    lpsrPaper::create (
      inputLineNumber);

  if (gLilypondOptions->fLilypondCompileDate) {
    // define headers and footers

    fPaper->
      setOddHeaderMarkup (
R"(\markup {
    \fill-line {
      \on-the-fly \not-first-page {
        \fromproperty #'page:page-number-string
        " "
        \fromproperty #'header:title
        " "
        \fromproperty #'header:subtitle
      }
    }
  }
)"
      );


    fPaper->
      setEvenHeaderMarkup (
R"(\markup {
    \fill-line {
      \on-the-fly \not-first-page {
        \fromproperty #'page:page-number-string
        " "
        \fromproperty #'header:title
        " "
        \fromproperty #'header:subtitle
      }
    }
  }
)"
      );

    stringstream s;

    s <<
R"(\markup {
    \tiny
    \column {
      \fill-line {
        #(string-append
)"
      <<
      "\"Music generated from MusicXML by xml2ly " <<
      currentVersionNumber () <<
      " and engraved by LilyPond \" (lilypond-version))" <<
R"(
      }
      \fill-line {
        "https://github.com/grame-cncm/libmusicxml/tree/lilypond - http://www.lilypond.org"
      }
      \fill-line { \italic { \modTimeAsString }}
    }
  }
)";

    fPaper->
      setOddFooterMarkup (
        s.str ());
  }

  // create the score layout
  fScoreLayout =
    lpsrLayout::create (
      inputLineNumber);

  // create the 'myBreakIsBreak' assoc
  {
    lpsrVarValAssoc::lpsrCommentedKind
      commentedKind =
        gLilypondOptions->fIgnoreLineBreaks
          ? lpsrVarValAssoc::kCommentedYes
          : lpsrVarValAssoc::kCommentedNo;

    fMyBreakIsBreakAssoc =
      lpsrVarValAssoc::create (
        inputLineNumber,
        commentedKind,
        lpsrVarValAssoc::kWithBackSlashNo,
        lpsrVarValAssoc::kLilypondMyBreak,
        lpsrVarValAssoc::kVarValSeparatorEqualSign,
        lpsrVarValAssoc::kQuotesAroundValueNo,
        "{ \\break }",
        lpsrVarValAssoc::g_LilyPondVarValAssocNoUnit,
        kFontStyleNone,
        kFontWeightNone,
        "Pick your choice from the next two lines as needed",
        lpsrVarValAssoc::kEndlNone);
  }

  // create the 'myBreakIsEmpty' assoc
  {
    lpsrVarValAssoc::lpsrCommentedKind
      commentedKind =
        gLilypondOptions->fIgnoreLineBreaks
          ? lpsrVarValAssoc::kCommentedNo
          : lpsrVarValAssoc::kCommentedYes;

    fMyBreakIsEmptyAssoc =
      lpsrVarValAssoc::create (
        inputLineNumber,
        commentedKind,
        lpsrVarValAssoc::kWithBackSlashNo,
        lpsrVarValAssoc::kLilypondMyBreak,
        lpsrVarValAssoc::kVarValSeparatorEqualSign,
        lpsrVarValAssoc::kQuotesAroundValueNo,
        "{ }",
        lpsrVarValAssoc::g_LilyPondVarValAssocNoUnit,
        kFontStyleNone,
        kFontWeightNone,
        lpsrVarValAssoc::g_LilyPondVarValAssocNoComment,
        lpsrVarValAssoc::kEndlOnce);
  }

  // create the 'myPageBreakIsPageBreak' assoc
  {
    lpsrVarValAssoc::lpsrCommentedKind
      commentedKind =
        gLilypondOptions->fIgnoreLineBreaks
          ? lpsrVarValAssoc::kCommentedYes
          : lpsrVarValAssoc::kCommentedNo;

    fMyPageBreakIsPageBreakAssoc =
      lpsrVarValAssoc::create (
        inputLineNumber,
        commentedKind,
        lpsrVarValAssoc::kWithBackSlashNo,
        lpsrVarValAssoc::kLilypondMyPageBreak,
        lpsrVarValAssoc::kVarValSeparatorEqualSign,
        lpsrVarValAssoc::kQuotesAroundValueNo,
        "{ \\pageBreak }",
        lpsrVarValAssoc::g_LilyPondVarValAssocNoUnit,
        kFontStyleNone,
        kFontWeightNone,
        "Pick your choice from the next two lines as needed",
        lpsrVarValAssoc::kEndlNone);
  }

  // create the 'myPageBreakIsEmpty' assoc
  {
    lpsrVarValAssoc::lpsrCommentedKind
      commentedKind =
        gLilypondOptions->fIgnoreLineBreaks
          ? lpsrVarValAssoc::kCommentedNo
          : lpsrVarValAssoc::kCommentedYes;

    fMyPageBreakIsEmptyAssoc =
      lpsrVarValAssoc::create (
        inputLineNumber,
        commentedKind,
        lpsrVarValAssoc::kWithBackSlashNo,
        lpsrVarValAssoc::kLilypondMyPageBreak,
        lpsrVarValAssoc::kVarValSeparatorEqualSign,
        lpsrVarValAssoc::kQuotesAroundValueNo,
        "{ }",
        lpsrVarValAssoc::g_LilyPondVarValAssocNoUnit,
        kFontStyleNone,
        kFontWeightNone,
        lpsrVarValAssoc::g_LilyPondVarValAssocNoComment,
        lpsrVarValAssoc::kEndlOnce);
  }

  if (gLilypondOptions->fGlobal) {
    // create the 'global' assoc
    fGlobalAssoc =
      lpsrVarValAssoc::create (
        inputLineNumber,
        lpsrVarValAssoc::kCommentedNo,
        lpsrVarValAssoc::kWithBackSlashNo,
        lpsrVarValAssoc::kLilypondGlobal,
        lpsrVarValAssoc::kVarValSeparatorEqualSign,
        lpsrVarValAssoc::kQuotesAroundValueNo,
        "{ }",
        lpsrVarValAssoc::g_LilyPondVarValAssocNoUnit,
        kFontStyleNone,
        kFontWeightNone,
        "Place whatever you need in the 'global' variable",
        lpsrVarValAssoc::kEndlOnce);
  }

  // create the score command
  fScoreBlock =
    lpsrBookPartBlock::create (
      inputLineNumber);
}

lpsrBookPart::~lpsrBookPart ()
{}

void lpsrBookPart::setGlobalStaffSize (float size)
{
  stringstream s;

  s << size;

  fGlobalStaffSizeAssoc->
    setVariableValue (s.str ());
}

void lpsrBookPart::setJianpuFileIncludeIsNeeded ()
{
  if (! fScmAndAccregSchemeModulesAreNeeded) {
    addJianpuFileIncludeToScore ();

    fJianpuFileIncludeIsNeeded = true;
  }
}

void lpsrBookPart::setScmAndAccregSchemeModulesAreNeeded ()
{
  if (! fScmAndAccregSchemeModulesAreNeeded) {
    addAccordionRegistrationSchemeModulesToScore ();

    fScmAndAccregSchemeModulesAreNeeded = true;
  }
}

void lpsrBookPart::setCustomShortBarLineSchemeFunctionIsNeeded ()
{
  if (! fCustomShortBarLineSchemeFunctionIsNeeded) {
    addCustomShortBarLineSchemeFunctionToScore ();

    fCustomShortBarLineSchemeFunctionIsNeeded = true;
  }
}

void lpsrBookPart::setTongueSchemeFunctionIsNeeded ()
{
  if (! fTongueSchemeFunctionIsNeeded) {
    addTongueSchemeFunctionToScore ();

    fTongueSchemeFunctionIsNeeded = true;
  }
}

void lpsrBookPart::setEditorialAccidentalSchemeFunctionIsNeeded ()
{
  if (! fEditorialAccidentalSchemeFunctionIsNeeded) {
    addEditorialAccidentalSchemeFunctionToScore ();

    fEditorialAccidentalSchemeFunctionIsNeeded = true;
  }
}

void lpsrBookPart::setDynamicsSchemeFunctionIsNeeded ()
{
  if (! fDynamicsSchemeFunctionIsNeeded) {
    addDynamicsSchemeFunctionToScore ();

    fDynamicsSchemeFunctionIsNeeded = true;
  }
}

void lpsrBookPart::setTupletsCurvedBracketsSchemeFunctionIsNeeded ()
{
  if (! fTupletsCurvedBracketsSchemeFunctionIsNeeded) {
    addTupletsCurvedBracketsSchemeFunctionToScore ();

    fTupletsCurvedBracketsSchemeFunctionIsNeeded = true;
  }
}

void lpsrBookPart::setAfterSchemeFunctionIsNeeded ()
{
  if (! fAfterSchemeFunctionIsNeeded) {
    addAfterSchemeFunctionToScore ();

    fAfterSchemeFunctionIsNeeded = true;
  }
}

void lpsrBookPart::setTempoRelationshipSchemeFunctionIsNeeded ()
{
  if (! fTempoRelationshipSchemeFunctionIsNeeded) {
    addTempoRelationshipSchemeFunctionToScore ();

    fTempoRelationshipSchemeFunctionIsNeeded = true;
  }
}

void lpsrBookPart::setGlissandoWithTextSchemeFunctionIsNeeded ()
{
  if (! fGlissandoWithTextSchemeFunctionIsNeeded) {
    addGlissandoWithTextSchemeFunctionsToScore ();

    fGlissandoWithTextSchemeFunctionIsNeeded = true;
  }
}

void lpsrBookPart::setDampMarkupIsNeeded ()
{
  if (! fDampMarkupIsNeeded) {
    addDampMarkupToScore ();

    fDampMarkupIsNeeded = true;
  }
}

void lpsrBookPart::setDampAllMarkupIsNeeded ()
{
  if (! fDampAllMarkupIsNeeded) {
    addDampAllMarkupToScore ();

    fDampAllMarkupIsNeeded = true;
  }
}

void lpsrBookPart::setWhiteNoteHeadsIsNeeded ()
{
  if (! fWhiteNoteHeadsIsNeeded) {
    addWhiteNoteHeadsToScore ();

    fWhiteNoteHeadsIsNeeded = true;
  }
}

void lpsrBookPart::addDateAndTimeSchemeFunctionsToScore ()
{
  string
    schemeFunctionName =
      "date & time",

    schemeFunctionDescription =
R"(
% A set of functions to obtain a source file's modification time.
)",

    schemeFunctionCode =
R"(
#(define comml           (object->string (command-line)))
#(define loc             (+ (string-rindex comml #\space ) 2))
#(define commllen        (- (string-length comml) 2))
#(define filen           (substring comml loc commllen))
#(define siz             (object->string (stat:size (stat filen))))
#(define ver             (object->string (lilypond-version)))
#(define dat             (strftime "%d/%m/%Y" (localtime (current-time))))
#(define tim             (strftime "%H:%M:%S" (localtime (current-time))))
#(define modTime         (stat:mtime (stat filen)))
#(define modTimeAsString (strftime "%d/%m/%Y - %H:%M:%S" (localtime modTime)))
)";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme functions for '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBookPart::addPointAndClickOffSchemeFunctionsToScore ()
{
  string
    schemeFunctionName =
      "pointAndClickOff",

    schemeFunctionDescription =
R"(
% \pointAndClickOff to reduce the size of the produced PDF file.
)",

    schemeFunctionCode =
R"(
\pointAndClickOff
)";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme functions for '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBookPart::addGlissandoWithTextSchemeFunctionsToScore ()
{
  string
    schemeFunctionName =
      "glissandoWithText",

    schemeFunctionDescription =
R"(
% \\glissandoTextOn/Off to get text along glissandos.
)",

    schemeFunctionCode =
R"(
% thanks to Thomas Morley for contributing this code

%% c/p from lily-library.scm (it is not public)
#(define (sign x)
  (if (= x 0)
      0
      (if (< x 0) -1 1)))

#(define (radians->degree radians)
  (/ (* radians 180) PI))

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% Glissando with text
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% Reads from Glissando.details
%%%%   - glissando-text
%%%%   - glissando-text-font-size
%%%%   - glissando-text-padding

#(define* ((gliss-plus-text #:optional always-add-text) grob)
  (let*  ((orig-grob (ly:grob-original grob))
          (broken-beams (ly:spanner-broken-into orig-grob))
          (stil (ly:line-spanner::print grob)))
    (if (or (null? broken-beams)
            (and (pair? broken-beams)
                 (or
                    always-add-text
                    (equal? grob (car broken-beams)))))
        (if (not (ly:stencil? stil))
            #f
            (let* ((layout (ly:grob-layout grob))
                   (line-thickness
                     (ly:output-def-lookup layout 'line-thickness))
                   (props
                     (ly:grob-alist-chain
                       grob
                       (ly:output-def-lookup layout 'text-font-defaults)))
                   (font
                     (ly:paper-get-font
                     layout
                     (cons
                       '((font-encoding . fetaMusic) (font-name . #f))
                       props)))
                   (trill-glyph
                     (ly:font-get-glyph font "scripts.trill_element"))
                   (trill-glyph-height
                     (interval-length (ly:stencil-extent trill-glyph Y)))
                   (zigzag-width
                     (ly:grob-property grob 'zigzag-width))
                   (thickness (ly:grob-property grob 'thickness))
                   (thick
                     (if (number? thickness)
                         (/ thickness 10)
                         line-thickness))
                   (style (ly:grob-property grob 'style))
                   (corr
                     (cond ((eq? style 'trill)
                             trill-glyph-height)
                           ((eq? style 'zigzag)
                             (+ thick zigzag-width))
                           (else 0)))
                   (stil-x-ext (ly:stencil-extent stil X))
                   (stil-y-ext (ly:stencil-extent stil Y))
                   (stil-x-length (- (cdr stil-x-ext) (car stil-x-ext)))
                   (stil-y-length (- (cdr stil-y-ext) (car stil-y-ext)))
                   (details (ly:grob-property grob 'details))
                   (gliss-text
                     (assoc-get 'glissando-text details "gliss."))
                   (gliss-text-font-size
                     (assoc-get 'glissando-text-font-size details -5))
                   (gliss-text-padding
                     (assoc-get 'glissando-text-padding details 0.5))
                   (left-bound-info (ly:grob-property grob 'left-bound-info))
                   (y-left (assoc-get 'Y left-bound-info))
                   (right-bound-info (ly:grob-property grob 'right-bound-info))
                   (y-right (assoc-get 'Y right-bound-info))
                   (slant (sign (- y-right y-left)))
                   (gradient
                     (/ (- stil-y-length corr) stil-x-length))
                   ;; `ly:stencil-rotate' needs an angle in degrees...
                   ;; TODO use ly:angle ?
                   (alpha
                     (radians->degree
                       (angle
                         (make-rectangular
                           stil-x-length
                           (- stil-y-length corr line-thickness)))))
                   (text-stencil
                     (grob-interpret-markup
                       grob
                         (make-halign-markup CENTER
                           (make-fontsize-markup
                             gliss-text-font-size
                             gliss-text))))
                   (text-stencil-height
                     (interval-length (ly:stencil-extent text-stencil Y)))
                   (y-move
                     (+
                       (/ text-stencil-height 2)
                       gliss-text-padding))
                   (rotated-text-stil
                     (ly:stencil-rotate text-stencil (* slant alpha) 0 0))
                   (text-center-X
                     (interval-center (ly:stencil-extent rotated-text-stil X)))
                   (translated-text-stencil
                     (ly:stencil-translate
                       rotated-text-stil
                       ;; Constuction-helpers
                       ;text-stencil
                       ;(make-cross-stencil '(0 . 0)) ;; not included atm
                       (cons
                         (+
                           (car stil-x-ext)
                           (/ stil-x-length 2)
                           (* slant -1 y-move gradient))
                         (+
                           (car stil-y-ext)
                           (/ stil-y-length 2)
                           y-move)))))
            (ly:stencil-add
              stil
              ;; Construction-helpers
              ;;
              ;(make-line-stencil
              ;  0.1
              ;  (+ (car stil-x-ext)(/ stil-x-length 2))
              ;  (+ (car stil-y-ext)(/ stil-y-length 2))
              ;  (+ (car stil-x-ext)(/ stil-x-length 2)(* slant -1 10 gradient))
              ;  10)
              ;;
              ;; (2) colors the text-part
              ;;
              ;(stencil-with-color translated-text-stencil red)
              translated-text-stencil
              )))
        stil)))

glissandoTextOn =
  \temporary \override Glissando.stencil =
    #(gliss-plus-text
      ;; change to true, if added text is wished for both parts of a broken
      ;; glissando
      ;; TODO added text at second parts needs to be improved, vertical
      ;; positioning is sometimes bad
      #f)

glissandoTextOff = \revert Glissando.stencil
)";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme functions for '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBookPart::addCustomShortBarLineSchemeFunctionToScore ()
{
  string
    schemeModulesName =
      "curstom short barline Scheme function",

    schemeModulesDescription =
R"(
% The function needed to produce curstom short barlines.
)",

    schemeModulesCode =
R"(
#(define ((make-custom-short-bar-line x y) grob extent)
   "Draw a short bar line."
   (let* ((short-staff (* 1/2 (ly:staff-symbol-staff-space grob)))
          (staff-line-thickness (ly:staff-symbol-line-thickness grob))
          (height (interval-end extent)))
     (bar-line::draw-filled-box
      (cons 0 (+ x staff-line-thickness))
      (cons (- height (* 7 short-staff) x) (- height short-staff x))
      staff-line-thickness
      extent
      grob)))

#(add-bar-glyph-print-procedure "/" (make-custom-short-bar-line 0.1 0.1))

#(define-bar-line "/" "/" #f #f)
)";


  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Including Jianpu definition file '" << schemeModulesName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeModulesName,
        schemeModulesDescription,
        schemeModulesCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeModulesName] =
    schemeFunction;
}

void lpsrBookPart::addJianpuFileIncludeToScore ()
{
  string
    schemeModulesName =
      "jianpu include file",

    schemeModulesDescription =
R"(
% The definitions needed to produce jianpu scores.
)",

    schemeModulesCode =
R"(
% From https://github.com/nybbs2003/lilypond-Jianpu
\include "jianpu10a.ly"
)";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Including Jianpu definition file '" << schemeModulesName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeModulesName,
        schemeModulesDescription,
        schemeModulesCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeModulesName] =
    schemeFunction;
}

void lpsrBookPart::addAccordionRegistrationSchemeModulesToScore ()
{
  string
    schemeModulesName =
      "scm & accreg",

    schemeModulesDescription =
R"(
% Two modules are to be used in the right order to use accordion registration.
)",

    schemeModulesCode =
R"(
#(use-modules (scm accreg))
)";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Using Scheme modules '" << schemeModulesName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeModulesName,
        schemeModulesDescription,
        schemeModulesCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeModulesName] =
    schemeFunction;
}

void lpsrBookPart::addTongueSchemeFunctionToScore ()
{
  string
    schemeFunctionName =
      "tongue",

    schemeFunctionDescription =
R"(
% Creates multiple tongue technicals, argument is a number.
% Example: 'c4 -\tongue #3' creates a triple tongue.
)",

    schemeFunctionCode =
R"(
tongue =
#(define-music-function (parser location dots) (integer?)
   (let ((script (make-music 'ArticulationEvent
                   'articulation-type "staccato")))
     (set! (ly:music-property script 'tweaks)
           (acons 'stencil
             (lambda (grob)
               (let ((stil (ly:script-interface::print grob)))
                 (let loop ((count (1- dots)) (new-stil stil))
                   (if (> count 0)
                       (loop (1- count)
                         (ly:stencil-combine-at-edge new-stil X RIGHT stil 0.2))
                       (ly:stencil-aligned-to new-stil X CENTER)))))
             (ly:music-property script 'tweaks)))
     script))
)";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme function '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBookPart::addEditorialAccidentalSchemeFunctionToScore ()
{
  string
    schemeFunctionName =
      "editorialAccidental",

    schemeFunctionDescription =
R"(
% Craetes editorial accidentals as LilyPond musica ficta.
% Example: '\editorialAccidental cis4'.
)",

    schemeFunctionCode =
R"(
editorialAccidental =
#(define-music-function
  (note)
  (ly:music?)
  #{
    \once\accidentalStyle forget
    \once\set suggestAccidentals = ##t
    #note
  #})
)";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme function '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBookPart::addDynamicsSchemeFunctionToScore ()
{
  string
    schemeFunctionName =
      "dynamics",

    schemeFunctionDescription =
R"(
% Creates variables define dynamics not native to LilyPond.
)",

    schemeFunctionCode =
R"(
rf = #(make-dynamic-script "rf")
sfpp = #(make-dynamic-script "sfpp")
sffz = #(make-dynamic-script "sffz")
ppppp = #(make-dynamic-script "ppppp")
pppppp = #(make-dynamic-script "pppppp")
fffff = #(make-dynamic-script "fffff")
ffffff = #(make-dynamic-script "ffffff")
)";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme function '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBookPart::addTupletsCurvedBracketsSchemeFunctionToScore ()
{
  string
    schemeFunctionName =
      "tupletsCurvedBrackets",

    schemeFunctionDescription =
R"(
% A function to draw curved tuplets brackets, not native to LilyPond.
% Thanks to Ben, mailto:soundsfromsound@gmail.com
)",

    schemeFunctionCode =
R"(
tupletsCurvedBrackets = {
  % Use slur-stencil
  \override TupletBracket.stencil = #ly:slur::print
  %% Use 'thickness from Slur
  \override TupletBracket.thickness = #1.2
  %% 'control-points need to be set
  \override TupletBracket.control-points =
  #(lambda (grob)
     (let* ((x-pos (ly:grob-property grob 'X-positions))
            (pos (ly:grob-property grob 'positions))
            (x-ln (interval-length x-pos))
            (dir (ly:grob-property grob 'direction))
            ;; read out the height of the TupletBracket, may be
            ;; negative!
            (height (- (cdr pos) (car pos)))
            ;; height-corr is introduced because sometimes the shape
            ;; of the slur needs to be adjusted.
            ;; It is used in the 2nd/3rd control-point.
            ;; The value of 0.3 is found by trial and error
            (height-corr (* 0.3 dir height))
            (edge-height (ly:grob-property grob 'edge-height
                           '(0.7 . 0.7)))
            (pad 1.0))
       (list
        ;; first cp
        (cons
         (+ (car x-pos) 0.5)
         (- (+ (* dir pad) (+ (car pos) (* -1 dir
                                          (car edge-height))))
           (if (= dir -1)
               (if (> height 3)
                   (/ dir 2.0)
                   0.0)
               (if (< height -3)
                   (/ dir 2.0)
                   0.0))))
        ;; second cp
        (cons
         (+ (car x-pos) (* x-ln 1/4))
         (+ (* dir pad) (+ (car pos) (* dir (+ 0.5 height-corr)))))
        ;; third cp
        (cons
         (+ (car x-pos) (* x-ln 3/4))
         (+ (* dir pad) (+ (cdr pos) (* dir (- 0.5 height-corr)))))
        ;; fourth cp
        (cons
         (- (cdr x-pos) 0.5)
         (+ (* dir pad) (+ (cdr pos) (* -1 dir (cdr edge-height)))))
        )))
  \override TupletBracket.staff-padding = #' ()
  #(define (invert-direction x) (if (eq? UP
                                         (ly:tuplet-bracket::calc-direction x)) DOWN UP))
  % \override TupletBracket.direction = #invert-direction
}
)";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme function '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBookPart::addAfterSchemeFunctionToScore ()
{
  string
    schemeFunctionName =
      "after",

    schemeFunctionDescription =
R"(
% A function to create events after given music.
% Thanks to David Kastrup for the inspiration!
)",

    schemeFunctionCode =
R"(
after =
#(define-music-function (t e m) (ly:duration? ly:music? ly:music?)
   #{
     \context Bottom <<
       #m
       { \skip $t <> -\tweak extra-spacing-width #empty-interval $e }
     >>
   #})
)";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme function '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBookPart::addTempoRelationshipSchemeFunctionToScore ()
{
  string
    schemeFunctionName =
      "tempoRelationship",

    schemeFunctionDescription =
R"(
% A function to create tempo relationships,
% such as 'b8 [ b8 ]' = '\tuplet 3/2 { b4 b8 }' for swing.
% See http://lsr.di.unimi.it/LSR/Item?id=204
)",

    schemeFunctionCode =
      // add ! before ( and after ) since the code contains )"
R"!(
tempoRelationshipStaffReduce = #-3

tempoRelationship =
#(define-music-function (parser location label parenthesized musicI musicII)
   (string? boolean? ly:music? ly:music?)
   (let* (
           (left-paren (if parenthesized "(" ""))
           (right-paren (if parenthesized ")" ""))
           )
     #{
       \tempo \markup {
         \line \general-align #Y #DOWN {
           % 1st column in line
           $label

           % 2nd column in line

           $left-paren

           \score {
             \new Staff \with {
               % reduce the font size a la cue
               fontSize = #tempoRelationshipStaffReduce
               \override StaffSymbol.staff-space = #(magstep tempoRelationshipStaffReduce)
               % hide the staff lines
               \override StaffSymbol.line-count = #0
               % align horizontally
               \override VerticalAxisGroup.Y-extent = #'(-0.85 . 0)
             }

             {
               % \override Score.SpacingSpanner.common-shortest-duration = #(ly:make-moment 1/2) % super-tight
               % \override Score.SpacingSpanner.common-shortest-duration = #(ly:make-moment 1/4) % tight
               % \override Score.SpacingSpanner.common-shortest-duration = #(ly:make-moment 3/16) % even
               \override Score.SpacingSpanner.common-shortest-duration = #(ly:make-moment 5/32) % even

               % the left music
               \relative c' { \stemUp $musicI }

               % the equivalence sign
               \once \override Score.TextScript.Y-offset = #-0.4
               s4.^\markup{
                 \halign #-1 "="
               }

               % the right music
               \relative c' { \stemUp $musicII }
             }

             \layout {
               indent = 0
               \context {
                 \Staff
                 \remove "Clef_engraver"
                 \remove "Time_signature_engraver"
               }
             } % layout end
           } % score end

           $right-paren

         } % line end
       } % markup end
     #}))
)!";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme function '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBookPart::addDampMarkupToScore ()
{
  string
    schemeFunctionName =
      "dampMarkup",

    schemeFunctionDescription =
R"(
% A function to create damp markups,
)",

    schemeFunctionCode =
      // add ! before ( and after ) since the code contains )"
R"!(
damp = \markup {
%  \scale #'(5 . 5)
  {
    \center-column {
      {
        \override #'(thickness . 1.8)
        \combine \draw-line #'(-1.5 . 0)
        \combine \draw-line #'(0 . -1.5)
        \combine \draw-line #'(0 . 1.5)
        \combine \draw-line #'(1.5 . 0)
        \draw-circle #0.8 #0.2 ##f
      }
    }
  }

}
)!";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme function '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBookPart::addDampAllMarkupToScore ()
{
  string
    schemeFunctionName =
      "dampAllMarkup",

    schemeFunctionDescription =
R"(
% A function to create damp all markups,
)",

    schemeFunctionCode =
      // add ! before ( and after ) since the code contains )"
R"!(
dampAll = \markup
%% do not use 'fontsize
%\scale #'(5 . 5)
{
  \combine \bold "O"
  \path #0.2
  #'((moveto -.4 .8)(lineto 2.2 .8)
      (closepath)
      (moveto .9 -.5)(lineto .9 2.1))
}
)!";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme function '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBookPart::addWhiteNoteHeadsToScore ()
{
  string
    schemeFunctionName =
      "whiteNoteHeads",

    schemeFunctionDescription =
R"(
% A function to display note shorter than a quarter with white heads,
% as in some ancient music scores
)",

    schemeFunctionCode =
      // add ! before ( and after ) since the code contains )"
R"!(
whiteNoteHeads =
#(define-music-function (music) (ly:music?)
   #{
     \temporary \override NoteHead.stencil = #ly:text-interface::print
     \temporary \override NoteHead.text = \markup {
       \musicglyph "noteheads.s1"
     }
     \omit \time 3/4
     \shiftDurations #1 #0 { #music }
     \omit \time 3/2
     \revert NoteHead.stencil
     \revert NoteHead.text
   #}
   )
)!";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme function '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

/* JMI
void lpsrBookPart::appendVoiceUseToStoreCommand (S_msrVoice voice)
{
  S_lpsrUseVoiceCommand
    useVoiceCommand =
      lpsrUseVoiceCommand::create (
        fInputLineNumber,
        voice);

  fScoreBlock->
    appendVoiceUseToParallelMusicBLock (useVoiceCommand);
}

void lpsrBookPart::appendLyricsUseToStoreCommand (S_msrStanza stanza)
{
  S_lpsrNewLyricsBlock
    newLyricsCommand =
      lpsrNewLyricsBlock::create (
        fInputLineNumber,
        stanza,
        stanza->getStanzaVoiceUplink ());

  fScoreBlock->
    appendLyricsUseToParallelMusicBLock (newLyricsCommand);
}
*/

void lpsrBookPart::acceptIn (basevisitor* v)
{
  if (gLpsrOptions->fTraceLpsrVisitors) {
    gLogIOstream <<
      "% ==> lpsrBookPart::acceptIn ()" <<
      endl;
  }

  if (visitor<S_lpsrBookPart>*
    p =
      dynamic_cast<visitor<S_lpsrBookPart>*> (v)) {
        S_lpsrBookPart elem = this;

        if (gLpsrOptions->fTraceLpsrVisitors) {
          gLogIOstream <<
            "% ==> Launching lpsrBookPart::visitStart ()" <<
            endl;
        }
        p->visitStart (elem);
  }
}

void lpsrBookPart::acceptOut (basevisitor* v)
{
  if (gLpsrOptions->fTraceLpsrVisitors) {
    gLogIOstream <<
      "% ==> lpsrBookPart::acceptOut ()" <<
      endl;
  }

  if (visitor<S_lpsrBookPart>*
    p =
      dynamic_cast<visitor<S_lpsrBookPart>*> (v)) {
        S_lpsrBookPart elem = this;

        if (gLpsrOptions->fTraceLpsrVisitors) {
          gLogIOstream <<
            "% ==> Launching lpsrBookPart::visitEnd ()" <<
            endl;
        }
        p->visitEnd (elem);
  }
}

void lpsrBookPart::browseData (basevisitor* v)
{
  if (gLpsrOptions->fTraceLpsrVisitors) {
    gLogIOstream <<
      "% ==> lpsrBookPart::browseData ()" <<
      endl;
  }

  {
    // browse the score LilyPond version
    msrBrowser<lpsrVarValAssoc> browser (v);
    browser.browse (*fLilypondVersion);
  }

  if (fInputSourceNameComment) {
    // browse the input source name comment
    msrBrowser<lpsrComment> browser (v);
    browser.browse (*fInputSourceNameComment);
  }

  if (fTranslationDateComment) {
    // browse the translation date comment
    msrBrowser<lpsrComment> browser (v);
    browser.browse (*fTranslationDateComment);
  }

  if (fCommandLineLongOptionsComment) {
    // browse the command line long options comment
    msrBrowser<lpsrComment> browser (v);
    browser.browse (*fCommandLineLongOptionsComment);
  }

  if (fCommandLineShortOptionsComment) {
    // browse the command line short options comment
    msrBrowser<lpsrComment> browser (v);
    browser.browse (*fCommandLineShortOptionsComment);
  }

  {
    // browse the score global size
    msrBrowser<lpsrSchemeVariable> browser (v);
    browser.browse (*fGlobalStaffSizeAssoc);
  }

  {
    // browse the Scheme function map
    for (
      map<string, S_lpsrSchemeFunction>::const_iterator i =
        fScoreSchemeFunctionsMap.begin ();
      i != fScoreSchemeFunctionsMap.end ();
      i++) {
      // browse the Scheme function
      msrBrowser<lpsrSchemeFunction> browser (v);
      browser.browse (*(*i).second);
    } // for
  }

  {
    // browse the score header
    msrBrowser<lpsrHeader> browser (v);
    browser.browse (*fHeader);
  }

  {
    // browse the score paper
    msrBrowser<lpsrPaper> browser (v);
    browser.browse (*fPaper);
  }

  {
    // browse the score layout
    msrBrowser<lpsrLayout> browser (v);
    browser.browse (*fScoreLayout);
  }

  {
    // browse the myBreakIsBreak assoc
    msrBrowser<lpsrVarValAssoc> browser (v);
    browser.browse (*fMyBreakIsBreakAssoc);
  }
  {
    // browse the myBreakIsEmpty assoc
    msrBrowser<lpsrVarValAssoc> browser (v);
    browser.browse (*fMyBreakIsEmptyAssoc);
  }

  {
    // browse the myPageBreakIsPageBreak assoc
    msrBrowser<lpsrVarValAssoc> browser (v);
    browser.browse (*fMyPageBreakIsPageBreakAssoc);
  }
  {
    // browse the myPageBreakIsEmpty assoc
    msrBrowser<lpsrVarValAssoc> browser (v);
    browser.browse (*fMyPageBreakIsEmptyAssoc);
  }

  if (fGlobalAssoc) {
    // browse the 'global' assoc
    msrBrowser<lpsrVarValAssoc> browser (v);
    browser.browse (*fGlobalAssoc);
  }

  {
    // browse the voices and stanzas list
    for (
      list<S_msrElement>::const_iterator i = fScoreElements.begin ();
      i != fScoreElements.end ();
      i++) {
      // browse the element
      msrBrowser<msrElement> browser (v);
      browser.browse (*(*i));
    } // for
  }

  {
    // browse the score command
    msrBrowser<lpsrBookPartBlock> browser (v);
    browser.browse (*fScoreBlock);
  }

  if (gLpsrOptions->fTraceLpsrVisitors) {
    gLogIOstream <<
      "% <== lpsrBookPart::browseData ()" <<
      endl;
  }
}

void lpsrBookPart::print (ostream& os)
{
  os <<
    "LPSR Score" <<
    endl <<
    endl;

  gIndenter++;

  // print the MSR structure (without the voices)
  fMsrScore->
    printSummary (os);
  os <<
    endl;

  // are some Scheme functions needed?
  const int fieldWidth = 42;

  os << left <<
    setw (fieldWidth) <<
    "TongueSchemeFunctionIsNeeded" << " : " <<
    booleanAsString (
      fTongueSchemeFunctionIsNeeded) <<
    endl <<
    setw (fieldWidth) <<
    "EditorialAccidentalSchemeFunctionIsNeeded" << " : " <<
    booleanAsString (
      fEditorialAccidentalSchemeFunctionIsNeeded) <<
    endl <<
    endl;

  // print LPSR basic information
  os <<
    fLilypondVersion <<
    endl <<

    fGlobalStaffSizeAssoc <<
    endl <<

    fHeader <<
    // no endl here

    fPaper <<
    endl <<

    fScoreLayout <<
    endl;

// myBreakAssoc,myPageBreakAssoc globalAssoc? JMI

  // print the voices
  if (fScoreElements.size ()) {
    list<S_msrElement>::const_iterator
      iBegin = fScoreElements.begin (),
      iEnd   = fScoreElements.end (),
      i      = iBegin;
    for ( ; ; ) {
      os << (*i);
      if (++i == iEnd) break;
      os << endl;
    } // for

    os <<
      endl;
  }

  // print the score block
  os <<
    fScoreBlock;

  gIndenter--;
}

ostream& operator<< (ostream& os, const S_lpsrBookPart& scr)
{
  scr->print (os);
  return os;
}

//______________________________________________________________________________
S_lpsrBookBlock lpsrBookBlock::create (
  int            inputLineNumber)
{
  lpsrBookBlock* o = new lpsrBookBlock (
    inputLineNumber);
  assert(o!=0);
  return o;
}

lpsrBookBlock::lpsrBookBlock (
  int            inputLineNumber)
    : lpsrElement (inputLineNumber)
{
  // create the score command parallel music
  fScoreBlockParallelMusicBLock =
    lpsrParallelMusicBLock::create (
      inputLineNumber,
      lpsrParallelMusicBLock::kEndOfLine);

  // create the score command layout
  fScoreBlockLayout =
    lpsrLayout::create (
      inputLineNumber);

  // create the score command midi
  string midiTempoDuration  = gLilypondOptions->fMidiTempo.first;
  int    midiTempoPerSecond = gLilypondOptions->fMidiTempo.second;

  fScoreBlockMidi =
    msrMidi::create (
      inputLineNumber,
      midiTempoDuration,
      midiTempoPerSecond);
}

lpsrBookBlock::~lpsrBookBlock ()
{}

void lpsrBookBlock::appendPartGroupBlockToScoreBlock (
  S_lpsrPartGroupBlock partGroupBlock)
{
#ifdef TRACE_OPTIONS
  if (gTraceOptions->fTracePartGroups) {
    gLogIOstream <<
      "Appending part group block " <<
       partGroupBlock-> getPartGroup ()-> getPartGroupCombinedName () <<
       " to LPSR score" <<
       endl;
  }
#endif

  fScoreBlockParallelMusicBLock->
    appendPartGroupBlockToParallelMusicBLock (
      partGroupBlock);

//               fScoreBlockElements.push_back(partGroupBlock);
}

/* JMI
void lpsrBookBlock::appendVoiceUseToParallelMusicBLock (
  S_lpsrUseVoiceCommand voiceUse)
{
#ifdef TRACE_OPTIONS
  if (gTraceOptions->fTraceVoices) {
    gLogIOstream <<
      "Appending the use of voice \"" <<
       voiceUse-> getVoice ()-> getVoiceName () <<
       "\" to LPSR score" <<
       endl;
  }
#endif

  fScoreBlockParallelMusicBLock->
    addElementToParallelMusicBLock (voiceUse);

//     JMI             fScoreBlockElements.push_back(voiceUse);
}

void lpsrBookBlock::appendLyricsUseToParallelMusicBLock (
  S_lpsrNewLyricsBlock lyricsUse)
{
#ifdef TRACE_OPTIONS
  if (gTraceOptions->fTraceLyrics) {
    gLogIOstream <<
      "Appending the use of stanza " <<
       lyricsUse-> getStanza ()-> getStanzaName () <<
       " to LPSR score" <<
       endl;
  }
#endif

  fScoreBlockParallelMusicBLock->
    addElementToParallelMusicBLock (lyricsUse);
}
*/

void lpsrBookBlock::acceptIn (basevisitor* v)
{
  if (gLpsrOptions->fTraceLpsrVisitors) {
    gLogIOstream <<
      "% ==> lpsrBookBlock::acceptIn ()" <<
      endl;
  }

  if (visitor<S_lpsrBookBlock>*
    p =
      dynamic_cast<visitor<S_lpsrBookBlock>*> (v)) {
        S_lpsrBookBlock elem = this;

        if (gLpsrOptions->fTraceLpsrVisitors) {
          gLogIOstream <<
            "% ==> Launching lpsrBookBlock::visitStart ()" <<
            endl;
        }
        p->visitStart (elem);
  }
}

void lpsrBookBlock::acceptOut (basevisitor* v)
{
  if (gLpsrOptions->fTraceLpsrVisitors) {
    gLogIOstream <<
      "% ==> lpsrBookBlock::acceptOut ()" <<
      endl;
  }

  if (visitor<S_lpsrBookBlock>*
    p =
      dynamic_cast<visitor<S_lpsrBookBlock>*> (v)) {
        S_lpsrBookBlock elem = this;

        if (gLpsrOptions->fTraceLpsrVisitors) {
          gLogIOstream <<
            "% ==> Launching lpsrBookBlock::visitEnd ()" <<
            endl;
        }
        p->visitEnd (elem);
  }
}

void lpsrBookBlock::browseData (basevisitor* v)
{
  if (gLpsrOptions->fTraceLpsrVisitors) {
    gLogIOstream <<
      "% ==> lpsrBookBlock::browseData ()" <<
      endl;
  }

  {
    // browse the score command parallel music
    msrBrowser<lpsrParallelMusicBLock> browser (v);
    browser.browse (*fScoreBlockParallelMusicBLock);
  }

/* JMI
  for (
    vector<S_msrElement>::const_iterator i = fScoreBlockElements.begin ();
    i != fScoreBlockElements.end ();
    i++) {
    // browse the element
 //   msrBrowser<msrElement> browser (v);
 //   browser.browse (*(*i));
  } // for
*/
  {
    // browse the score command layout
    msrBrowser<lpsrLayout> browser (v);
    browser.browse (*fScoreBlockLayout);
  }

  {
    // browse the score command midi
    msrBrowser<msrMidi> browser (v);
    browser.browse (*fScoreBlockMidi);
  }

  if (gLpsrOptions->fTraceLpsrVisitors) {
    gLogIOstream <<
      "% <== lpsrBookBlock::browseData ()" <<
      endl;
  }
}

void lpsrBookBlock::print (ostream& os)
{
  os << "ScoreBlock" << endl << endl;

  gIndenter++;

  os <<
    fScoreBlockParallelMusicBLock <<
    endl;

  os <<
    fScoreBlockLayout <<
    endl;

  os <<
    fScoreBlockMidi <<
    endl;

  gIndenter--;
}

ostream& operator<< (ostream& os, const S_lpsrBookBlock& scr)
{
  scr->print (os);
  return os;
}

//______________________________________________________________________________
S_lpsrBook lpsrBook::create (
  int            inputLineNumber,
  S_msrScore     mScore)
{
  lpsrBook* o = new lpsrBook (
    inputLineNumber, mScore);
  assert(o!=0);
  return o;
}

lpsrBook::lpsrBook (
  int            inputLineNumber,
  S_msrScore     mScore)
    : lpsrElement (inputLineNumber)
{
  fMsrScore = mScore;

  // create the LilyPond version assoc
  fLilypondVersion =
    lpsrVarValAssoc::create (
      inputLineNumber,
      lpsrVarValAssoc::kCommentedNo,
      lpsrVarValAssoc::kWithBackSlashYes,
      lpsrVarValAssoc::kLibraryVersion,
      lpsrVarValAssoc::kVarValSeparatorSpace,
      lpsrVarValAssoc::kQuotesAroundValueYes,
      "2.20.0",
      lpsrVarValAssoc::g_LilyPondVarValAssocNoUnit,
      kFontStyleNone,
      kFontWeightNone,
      lpsrVarValAssoc::g_LilyPondVarValAssocNoComment,
      lpsrVarValAssoc::kEndlOnce);

  // should the initial comments about xml2ly and the options used
  // be generated?
  if (gLilypondOptions->fXml2lyInfos) {
    // create the input source name comment
    {
      stringstream s;

      s <<
        "Generated by xml2ly " << currentVersionNumber () <<
        " from ";

      if (gGeneralOptions->fInputSourceName == "-") {
        s << "standard input";
      }
      else {
        s << "\"" << gGeneralOptions->fInputSourceName << "\"";
      }

      s <<
        endl <<
        "% on " << gGeneralOptions->fTranslationDate <<
        endl;

      fInputSourceNameComment =
        lpsrComment::create (
          inputLineNumber,
          s.str (),
          lpsrComment::kNoGapAfterwards);
    }

    // create the translation date comment
    {
      stringstream s;

      s <<
        "% Translation command was:";

      fTranslationDateComment =
        lpsrComment::create (
          inputLineNumber,
          s.str (),
          lpsrComment::kNoGapAfterwards);
    }

    // do the command line long and short options differ?
    bool
      longAndShortOptionsDiffer =
      gGeneralOptions->fCommandLineWithShortOptions
        !=
      gGeneralOptions->fCommandLineWithLongOptions;


  // create the command line long options comment
  {
    stringstream s;

    s <<
      gTab <<
      gGeneralOptions->fCommandLineWithLongOptions;

    if (longAndShortOptionsDiffer) {
      s <<
        endl <<
        "% or:";
    }

    fCommandLineLongOptionsComment =
      lpsrComment::create (
        inputLineNumber,
        s.str (),
        longAndShortOptionsDiffer
          ? lpsrComment::kNoGapAfterwards
          : lpsrComment::kGapAfterwards);
  }

  if (longAndShortOptionsDiffer) {
    // create the command line short options comment
    stringstream s;

    s <<
      gTab <<
      gGeneralOptions->fCommandLineWithShortOptions;

    fCommandLineShortOptionsComment =
      lpsrComment::create (
        inputLineNumber,
        s.str (),
        lpsrComment::kGapAfterwards);
  }
}

  // create the global staff size assoc
  fGlobalStaffSizeAssoc =
    lpsrSchemeVariable::create (
      inputLineNumber,
      lpsrSchemeVariable::kCommentedNo,
      "set-global-staff-size",
      "20", // the LilyPond default
      "Comment or adapt next line as needed (default is 20)",
      lpsrSchemeVariable::kEndlTwice);

  // initialize Scheme functions informations
  fTongueSchemeFunctionIsNeeded              = false;
  fCustomShortBarLineSchemeFunctionIsNeeded  = false;
  fEditorialAccidentalSchemeFunctionIsNeeded = false;

  if (gLilypondOptions->fLilypondCompileDate) {
    // create the date and time functions
    addDateAndTimeSchemeFunctionsToScore ();
  }

  if (gLilypondOptions->fPointAndClickOff) {
    // create the pointAndClickOff command
    addPointAndClickOffSchemeFunctionsToScore ();
  }

  if (gLilypondOptions->fPointAndClickOff) {
    // create the glissandoWithText command
    addGlissandoWithTextSchemeFunctionsToScore ();
  }

  if (gLilypondOptions->fJianpu) {
    // create the Jianpu include command JMI
  }

  // create the header
  fHeader =
    lpsrHeader::create (
      inputLineNumber);

  // create the paper
  fPaper =
    lpsrPaper::create (
      inputLineNumber);

  if (gLilypondOptions->fLilypondCompileDate) {
    // define headers and footers

    fPaper->
      setOddHeaderMarkup (
R"(\markup {
    \fill-line {
      \on-the-fly \not-first-page {
        \fromproperty #'page:page-number-string
        " "
        \fromproperty #'header:title
        " "
        \fromproperty #'header:subtitle
      }
    }
  }
)"
      );


    fPaper->
      setEvenHeaderMarkup (
R"(\markup {
    \fill-line {
      \on-the-fly \not-first-page {
        \fromproperty #'page:page-number-string
        " "
        \fromproperty #'header:title
        " "
        \fromproperty #'header:subtitle
      }
    }
  }
)"
      );

    stringstream s;

    s <<
R"(\markup {
    \tiny
    \column {
      \fill-line {
        #(string-append
)"
      <<
      "\"Music generated from MusicXML by xml2ly " <<
      currentVersionNumber () <<
      " and engraved by LilyPond \" (lilypond-version))" <<
R"(
      }
      \fill-line {
        "https://github.com/grame-cncm/libmusicxml/tree/lilypond - http://www.lilypond.org"
      }
      \fill-line { \italic { \modTimeAsString }}
    }
  }
)";

    fPaper->
      setOddFooterMarkup (
        s.str ());
  }

  // create the score layout
  fScoreLayout =
    lpsrLayout::create (
      inputLineNumber);

  // create the 'myBreakIsBreak' assoc
  {
    lpsrVarValAssoc::lpsrCommentedKind
      commentedKind =
        gLilypondOptions->fIgnoreLineBreaks
          ? lpsrVarValAssoc::kCommentedYes
          : lpsrVarValAssoc::kCommentedNo;

    fMyBreakIsBreakAssoc =
      lpsrVarValAssoc::create (
        inputLineNumber,
        commentedKind,
        lpsrVarValAssoc::kWithBackSlashNo,
        lpsrVarValAssoc::kLilypondMyBreak,
        lpsrVarValAssoc::kVarValSeparatorEqualSign,
        lpsrVarValAssoc::kQuotesAroundValueNo,
        "{ \\break }",
        lpsrVarValAssoc::g_LilyPondVarValAssocNoUnit,
        kFontStyleNone,
        kFontWeightNone,
        "Pick your choice from the next two lines as needed",
        lpsrVarValAssoc::kEndlNone);
  }

  // create the 'myBreakIsEmpty' assoc
  {
    lpsrVarValAssoc::lpsrCommentedKind
      commentedKind =
        gLilypondOptions->fIgnoreLineBreaks
          ? lpsrVarValAssoc::kCommentedNo
          : lpsrVarValAssoc::kCommentedYes;

    fMyBreakIsEmptyAssoc =
      lpsrVarValAssoc::create (
        inputLineNumber,
        commentedKind,
        lpsrVarValAssoc::kWithBackSlashNo,
        lpsrVarValAssoc::kLilypondMyBreak,
        lpsrVarValAssoc::kVarValSeparatorEqualSign,
        lpsrVarValAssoc::kQuotesAroundValueNo,
        "{ }",
        lpsrVarValAssoc::g_LilyPondVarValAssocNoUnit,
        kFontStyleNone,
        kFontWeightNone,
        lpsrVarValAssoc::g_LilyPondVarValAssocNoComment,
        lpsrVarValAssoc::kEndlOnce);
  }

  // create the 'myPageBreakIsPageBreak' assoc
  {
    lpsrVarValAssoc::lpsrCommentedKind
      commentedKind =
        gLilypondOptions->fIgnoreLineBreaks
          ? lpsrVarValAssoc::kCommentedYes
          : lpsrVarValAssoc::kCommentedNo;

    fMyPageBreakIsPageBreakAssoc =
      lpsrVarValAssoc::create (
        inputLineNumber,
        commentedKind,
        lpsrVarValAssoc::kWithBackSlashNo,
        lpsrVarValAssoc::kLilypondMyPageBreak,
        lpsrVarValAssoc::kVarValSeparatorEqualSign,
        lpsrVarValAssoc::kQuotesAroundValueNo,
        "{ \\pageBreak }",
        lpsrVarValAssoc::g_LilyPondVarValAssocNoUnit,
        kFontStyleNone,
        kFontWeightNone,
        "Pick your choice from the next two lines as needed",
        lpsrVarValAssoc::kEndlNone);
  }

  // create the 'myPageBreakIsEmpty' assoc
  {
    lpsrVarValAssoc::lpsrCommentedKind
      commentedKind =
        gLilypondOptions->fIgnoreLineBreaks
          ? lpsrVarValAssoc::kCommentedNo
          : lpsrVarValAssoc::kCommentedYes;

    fMyPageBreakIsEmptyAssoc =
      lpsrVarValAssoc::create (
        inputLineNumber,
        commentedKind,
        lpsrVarValAssoc::kWithBackSlashNo,
        lpsrVarValAssoc::kLilypondMyPageBreak,
        lpsrVarValAssoc::kVarValSeparatorEqualSign,
        lpsrVarValAssoc::kQuotesAroundValueNo,
        "{ }",
        lpsrVarValAssoc::g_LilyPondVarValAssocNoUnit,
        kFontStyleNone,
        kFontWeightNone,
        lpsrVarValAssoc::g_LilyPondVarValAssocNoComment,
        lpsrVarValAssoc::kEndlOnce);
  }

  if (gLilypondOptions->fGlobal) {
    // create the 'global' assoc
    fGlobalAssoc =
      lpsrVarValAssoc::create (
        inputLineNumber,
        lpsrVarValAssoc::kCommentedNo,
        lpsrVarValAssoc::kWithBackSlashNo,
        lpsrVarValAssoc::kLilypondGlobal,
        lpsrVarValAssoc::kVarValSeparatorEqualSign,
        lpsrVarValAssoc::kQuotesAroundValueNo,
        "{ }",
        lpsrVarValAssoc::g_LilyPondVarValAssocNoUnit,
        kFontStyleNone,
        kFontWeightNone,
        "Place whatever you need in the 'global' variable",
        lpsrVarValAssoc::kEndlOnce);
  }

  // create the score command
  fScoreBlock =
    lpsrBookBlock::create (
      inputLineNumber);
}

lpsrBook::~lpsrBook ()
{}

void lpsrBook::setGlobalStaffSize (float size)
{
  stringstream s;

  s << size;

  fGlobalStaffSizeAssoc->
    setVariableValue (s.str ());
}

void lpsrBook::setJianpuFileIncludeIsNeeded ()
{
  if (! fScmAndAccregSchemeModulesAreNeeded) {
    addJianpuFileIncludeToScore ();

    fJianpuFileIncludeIsNeeded = true;
  }
}

void lpsrBook::setScmAndAccregSchemeModulesAreNeeded ()
{
  if (! fScmAndAccregSchemeModulesAreNeeded) {
    addAccordionRegistrationSchemeModulesToScore ();

    fScmAndAccregSchemeModulesAreNeeded = true;
  }
}

void lpsrBook::setCustomShortBarLineSchemeFunctionIsNeeded ()
{
  if (! fCustomShortBarLineSchemeFunctionIsNeeded) {
    addCustomShortBarLineSchemeFunctionToScore ();

    fCustomShortBarLineSchemeFunctionIsNeeded = true;
  }
}

void lpsrBook::setTongueSchemeFunctionIsNeeded ()
{
  if (! fTongueSchemeFunctionIsNeeded) {
    addTongueSchemeFunctionToScore ();

    fTongueSchemeFunctionIsNeeded = true;
  }
}

void lpsrBook::setEditorialAccidentalSchemeFunctionIsNeeded ()
{
  if (! fEditorialAccidentalSchemeFunctionIsNeeded) {
    addEditorialAccidentalSchemeFunctionToScore ();

    fEditorialAccidentalSchemeFunctionIsNeeded = true;
  }
}

void lpsrBook::setDynamicsSchemeFunctionIsNeeded ()
{
  if (! fDynamicsSchemeFunctionIsNeeded) {
    addDynamicsSchemeFunctionToScore ();

    fDynamicsSchemeFunctionIsNeeded = true;
  }
}

void lpsrBook::setTupletsCurvedBracketsSchemeFunctionIsNeeded ()
{
  if (! fTupletsCurvedBracketsSchemeFunctionIsNeeded) {
    addTupletsCurvedBracketsSchemeFunctionToScore ();

    fTupletsCurvedBracketsSchemeFunctionIsNeeded = true;
  }
}

void lpsrBook::setAfterSchemeFunctionIsNeeded ()
{
  if (! fAfterSchemeFunctionIsNeeded) {
    addAfterSchemeFunctionToScore ();

    fAfterSchemeFunctionIsNeeded = true;
  }
}

void lpsrBook::setTempoRelationshipSchemeFunctionIsNeeded ()
{
  if (! fTempoRelationshipSchemeFunctionIsNeeded) {
    addTempoRelationshipSchemeFunctionToScore ();

    fTempoRelationshipSchemeFunctionIsNeeded = true;
  }
}

void lpsrBook::setGlissandoWithTextSchemeFunctionIsNeeded ()
{
  if (! fGlissandoWithTextSchemeFunctionIsNeeded) {
    addGlissandoWithTextSchemeFunctionsToScore ();

    fGlissandoWithTextSchemeFunctionIsNeeded = true;
  }
}

void lpsrBook::setDampMarkupIsNeeded ()
{
  if (! fDampMarkupIsNeeded) {
    addDampMarkupToScore ();

    fDampMarkupIsNeeded = true;
  }
}

void lpsrBook::setDampAllMarkupIsNeeded ()
{
  if (! fDampAllMarkupIsNeeded) {
    addDampAllMarkupToScore ();

    fDampAllMarkupIsNeeded = true;
  }
}

void lpsrBook::setWhiteNoteHeadsIsNeeded ()
{
  if (! fWhiteNoteHeadsIsNeeded) {
    addWhiteNoteHeadsToScore ();

    fWhiteNoteHeadsIsNeeded = true;
  }
}

void lpsrBook::addDateAndTimeSchemeFunctionsToScore ()
{
  string
    schemeFunctionName =
      "date & time",

    schemeFunctionDescription =
R"(
% A set of functions to obtain a source file's modification time.
)",

    schemeFunctionCode =
R"(
#(define comml           (object->string (command-line)))
#(define loc             (+ (string-rindex comml #\space ) 2))
#(define commllen        (- (string-length comml) 2))
#(define filen           (substring comml loc commllen))
#(define siz             (object->string (stat:size (stat filen))))
#(define ver             (object->string (lilypond-version)))
#(define dat             (strftime "%d/%m/%Y" (localtime (current-time))))
#(define tim             (strftime "%H:%M:%S" (localtime (current-time))))
#(define modTime         (stat:mtime (stat filen)))
#(define modTimeAsString (strftime "%d/%m/%Y - %H:%M:%S" (localtime modTime)))
)";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme functions for '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBook::addPointAndClickOffSchemeFunctionsToScore ()
{
  string
    schemeFunctionName =
      "pointAndClickOff",

    schemeFunctionDescription =
R"(
% \pointAndClickOff to reduce the size of the produced PDF file.
)",

    schemeFunctionCode =
R"(
\pointAndClickOff
)";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme functions for '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBook::addGlissandoWithTextSchemeFunctionsToScore ()
{
  string
    schemeFunctionName =
      "glissandoWithText",

    schemeFunctionDescription =
R"(
% \\glissandoTextOn/Off to get text along glissandos.
)",

    schemeFunctionCode =
R"(
% thanks to Thomas Morley for contributing this code

%% c/p from lily-library.scm (it is not public)
#(define (sign x)
  (if (= x 0)
      0
      (if (< x 0) -1 1)))

#(define (radians->degree radians)
  (/ (* radians 180) PI))

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% Glissando with text
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% Reads from Glissando.details
%%%%   - glissando-text
%%%%   - glissando-text-font-size
%%%%   - glissando-text-padding

#(define* ((gliss-plus-text #:optional always-add-text) grob)
  (let*  ((orig-grob (ly:grob-original grob))
          (broken-beams (ly:spanner-broken-into orig-grob))
          (stil (ly:line-spanner::print grob)))
    (if (or (null? broken-beams)
            (and (pair? broken-beams)
                 (or
                    always-add-text
                    (equal? grob (car broken-beams)))))
        (if (not (ly:stencil? stil))
            #f
            (let* ((layout (ly:grob-layout grob))
                   (line-thickness
                     (ly:output-def-lookup layout 'line-thickness))
                   (props
                     (ly:grob-alist-chain
                       grob
                       (ly:output-def-lookup layout 'text-font-defaults)))
                   (font
                     (ly:paper-get-font
                     layout
                     (cons
                       '((font-encoding . fetaMusic) (font-name . #f))
                       props)))
                   (trill-glyph
                     (ly:font-get-glyph font "scripts.trill_element"))
                   (trill-glyph-height
                     (interval-length (ly:stencil-extent trill-glyph Y)))
                   (zigzag-width
                     (ly:grob-property grob 'zigzag-width))
                   (thickness (ly:grob-property grob 'thickness))
                   (thick
                     (if (number? thickness)
                         (/ thickness 10)
                         line-thickness))
                   (style (ly:grob-property grob 'style))
                   (corr
                     (cond ((eq? style 'trill)
                             trill-glyph-height)
                           ((eq? style 'zigzag)
                             (+ thick zigzag-width))
                           (else 0)))
                   (stil-x-ext (ly:stencil-extent stil X))
                   (stil-y-ext (ly:stencil-extent stil Y))
                   (stil-x-length (- (cdr stil-x-ext) (car stil-x-ext)))
                   (stil-y-length (- (cdr stil-y-ext) (car stil-y-ext)))
                   (details (ly:grob-property grob 'details))
                   (gliss-text
                     (assoc-get 'glissando-text details "gliss."))
                   (gliss-text-font-size
                     (assoc-get 'glissando-text-font-size details -5))
                   (gliss-text-padding
                     (assoc-get 'glissando-text-padding details 0.5))
                   (left-bound-info (ly:grob-property grob 'left-bound-info))
                   (y-left (assoc-get 'Y left-bound-info))
                   (right-bound-info (ly:grob-property grob 'right-bound-info))
                   (y-right (assoc-get 'Y right-bound-info))
                   (slant (sign (- y-right y-left)))
                   (gradient
                     (/ (- stil-y-length corr) stil-x-length))
                   ;; `ly:stencil-rotate' needs an angle in degrees...
                   ;; TODO use ly:angle ?
                   (alpha
                     (radians->degree
                       (angle
                         (make-rectangular
                           stil-x-length
                           (- stil-y-length corr line-thickness)))))
                   (text-stencil
                     (grob-interpret-markup
                       grob
                         (make-halign-markup CENTER
                           (make-fontsize-markup
                             gliss-text-font-size
                             gliss-text))))
                   (text-stencil-height
                     (interval-length (ly:stencil-extent text-stencil Y)))
                   (y-move
                     (+
                       (/ text-stencil-height 2)
                       gliss-text-padding))
                   (rotated-text-stil
                     (ly:stencil-rotate text-stencil (* slant alpha) 0 0))
                   (text-center-X
                     (interval-center (ly:stencil-extent rotated-text-stil X)))
                   (translated-text-stencil
                     (ly:stencil-translate
                       rotated-text-stil
                       ;; Constuction-helpers
                       ;text-stencil
                       ;(make-cross-stencil '(0 . 0)) ;; not included atm
                       (cons
                         (+
                           (car stil-x-ext)
                           (/ stil-x-length 2)
                           (* slant -1 y-move gradient))
                         (+
                           (car stil-y-ext)
                           (/ stil-y-length 2)
                           y-move)))))
            (ly:stencil-add
              stil
              ;; Construction-helpers
              ;;
              ;(make-line-stencil
              ;  0.1
              ;  (+ (car stil-x-ext)(/ stil-x-length 2))
              ;  (+ (car stil-y-ext)(/ stil-y-length 2))
              ;  (+ (car stil-x-ext)(/ stil-x-length 2)(* slant -1 10 gradient))
              ;  10)
              ;;
              ;; (2) colors the text-part
              ;;
              ;(stencil-with-color translated-text-stencil red)
              translated-text-stencil
              )))
        stil)))

glissandoTextOn =
  \temporary \override Glissando.stencil =
    #(gliss-plus-text
      ;; change to true, if added text is wished for both parts of a broken
      ;; glissando
      ;; TODO added text at second parts needs to be improved, vertical
      ;; positioning is sometimes bad
      #f)

glissandoTextOff = \revert Glissando.stencil
)";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme functions for '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBook::addCustomShortBarLineSchemeFunctionToScore ()
{
  string
    schemeModulesName =
      "curstom short barline Scheme function",

    schemeModulesDescription =
R"(
% The function needed to produce curstom short barlines.
)",

    schemeModulesCode =
R"(
#(define ((make-custom-short-bar-line x y) grob extent)
   "Draw a short bar line."
   (let* ((short-staff (* 1/2 (ly:staff-symbol-staff-space grob)))
          (staff-line-thickness (ly:staff-symbol-line-thickness grob))
          (height (interval-end extent)))
     (bar-line::draw-filled-box
      (cons 0 (+ x staff-line-thickness))
      (cons (- height (* 7 short-staff) x) (- height short-staff x))
      staff-line-thickness
      extent
      grob)))

#(add-bar-glyph-print-procedure "/" (make-custom-short-bar-line 0.1 0.1))

#(define-bar-line "/" "/" #f #f)
)";


  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Including Jianpu definition file '" << schemeModulesName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeModulesName,
        schemeModulesDescription,
        schemeModulesCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeModulesName] =
    schemeFunction;
}

void lpsrBook::addJianpuFileIncludeToScore ()
{
  string
    schemeModulesName =
      "jianpu include file",

    schemeModulesDescription =
R"(
% The definitions needed to produce jianpu scores.
)",

    schemeModulesCode =
R"(
% From https://github.com/nybbs2003/lilypond-Jianpu
\include "jianpu10a.ly"
)";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Including Jianpu definition file '" << schemeModulesName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeModulesName,
        schemeModulesDescription,
        schemeModulesCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeModulesName] =
    schemeFunction;
}

void lpsrBook::addAccordionRegistrationSchemeModulesToScore ()
{
  string
    schemeModulesName =
      "scm & accreg",

    schemeModulesDescription =
R"(
% Two modules are to be used in the right order to use accordion registration.
)",

    schemeModulesCode =
R"(
#(use-modules (scm accreg))
)";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Using Scheme modules '" << schemeModulesName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeModulesName,
        schemeModulesDescription,
        schemeModulesCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeModulesName] =
    schemeFunction;
}

void lpsrBook::addTongueSchemeFunctionToScore ()
{
  string
    schemeFunctionName =
      "tongue",

    schemeFunctionDescription =
R"(
% Creates multiple tongue technicals, argument is a number.
% Example: 'c4 -\tongue #3' creates a triple tongue.
)",

    schemeFunctionCode =
R"(
tongue =
#(define-music-function (parser location dots) (integer?)
   (let ((script (make-music 'ArticulationEvent
                   'articulation-type "staccato")))
     (set! (ly:music-property script 'tweaks)
           (acons 'stencil
             (lambda (grob)
               (let ((stil (ly:script-interface::print grob)))
                 (let loop ((count (1- dots)) (new-stil stil))
                   (if (> count 0)
                       (loop (1- count)
                         (ly:stencil-combine-at-edge new-stil X RIGHT stil 0.2))
                       (ly:stencil-aligned-to new-stil X CENTER)))))
             (ly:music-property script 'tweaks)))
     script))
)";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme function '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBook::addEditorialAccidentalSchemeFunctionToScore ()
{
  string
    schemeFunctionName =
      "editorialAccidental",

    schemeFunctionDescription =
R"(
% Craetes editorial accidentals as LilyPond musica ficta.
% Example: '\editorialAccidental cis4'.
)",

    schemeFunctionCode =
R"(
editorialAccidental =
#(define-music-function
  (note)
  (ly:music?)
  #{
    \once\accidentalStyle forget
    \once\set suggestAccidentals = ##t
    #note
  #})
)";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme function '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBook::addDynamicsSchemeFunctionToScore ()
{
  string
    schemeFunctionName =
      "dynamics",

    schemeFunctionDescription =
R"(
% Creates variables define dynamics not native to LilyPond.
)",

    schemeFunctionCode =
R"(
rf = #(make-dynamic-script "rf")
sfpp = #(make-dynamic-script "sfpp")
sffz = #(make-dynamic-script "sffz")
ppppp = #(make-dynamic-script "ppppp")
pppppp = #(make-dynamic-script "pppppp")
fffff = #(make-dynamic-script "fffff")
ffffff = #(make-dynamic-script "ffffff")
)";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme function '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBook::addTupletsCurvedBracketsSchemeFunctionToScore ()
{
  string
    schemeFunctionName =
      "tupletsCurvedBrackets",

    schemeFunctionDescription =
R"(
% A function to draw curved tuplets brackets, not native to LilyPond.
% Thanks to Ben, mailto:soundsfromsound@gmail.com
)",

    schemeFunctionCode =
R"(
tupletsCurvedBrackets = {
  % Use slur-stencil
  \override TupletBracket.stencil = #ly:slur::print
  %% Use 'thickness from Slur
  \override TupletBracket.thickness = #1.2
  %% 'control-points need to be set
  \override TupletBracket.control-points =
  #(lambda (grob)
     (let* ((x-pos (ly:grob-property grob 'X-positions))
            (pos (ly:grob-property grob 'positions))
            (x-ln (interval-length x-pos))
            (dir (ly:grob-property grob 'direction))
            ;; read out the height of the TupletBracket, may be
            ;; negative!
            (height (- (cdr pos) (car pos)))
            ;; height-corr is introduced because sometimes the shape
            ;; of the slur needs to be adjusted.
            ;; It is used in the 2nd/3rd control-point.
            ;; The value of 0.3 is found by trial and error
            (height-corr (* 0.3 dir height))
            (edge-height (ly:grob-property grob 'edge-height
                           '(0.7 . 0.7)))
            (pad 1.0))
       (list
        ;; first cp
        (cons
         (+ (car x-pos) 0.5)
         (- (+ (* dir pad) (+ (car pos) (* -1 dir
                                          (car edge-height))))
           (if (= dir -1)
               (if (> height 3)
                   (/ dir 2.0)
                   0.0)
               (if (< height -3)
                   (/ dir 2.0)
                   0.0))))
        ;; second cp
        (cons
         (+ (car x-pos) (* x-ln 1/4))
         (+ (* dir pad) (+ (car pos) (* dir (+ 0.5 height-corr)))))
        ;; third cp
        (cons
         (+ (car x-pos) (* x-ln 3/4))
         (+ (* dir pad) (+ (cdr pos) (* dir (- 0.5 height-corr)))))
        ;; fourth cp
        (cons
         (- (cdr x-pos) 0.5)
         (+ (* dir pad) (+ (cdr pos) (* -1 dir (cdr edge-height)))))
        )))
  \override TupletBracket.staff-padding = #' ()
  #(define (invert-direction x) (if (eq? UP
                                         (ly:tuplet-bracket::calc-direction x)) DOWN UP))
  % \override TupletBracket.direction = #invert-direction
}
)";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme function '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBook::addAfterSchemeFunctionToScore ()
{
  string
    schemeFunctionName =
      "after",

    schemeFunctionDescription =
R"(
% A function to create events after given music.
% Thanks to David Kastrup for the inspiration!
)",

    schemeFunctionCode =
R"(
after =
#(define-music-function (t e m) (ly:duration? ly:music? ly:music?)
   #{
     \context Bottom <<
       #m
       { \skip $t <> -\tweak extra-spacing-width #empty-interval $e }
     >>
   #})
)";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme function '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBook::addTempoRelationshipSchemeFunctionToScore ()
{
  string
    schemeFunctionName =
      "tempoRelationship",

    schemeFunctionDescription =
R"(
% A function to create tempo relationships,
% such as 'b8 [ b8 ]' = '\tuplet 3/2 { b4 b8 }' for swing.
% See http://lsr.di.unimi.it/LSR/Item?id=204
)",

    schemeFunctionCode =
      // add ! before ( and after ) since the code contains )"
R"!(
tempoRelationshipStaffReduce = #-3

tempoRelationship =
#(define-music-function (parser location label parenthesized musicI musicII)
   (string? boolean? ly:music? ly:music?)
   (let* (
           (left-paren (if parenthesized "(" ""))
           (right-paren (if parenthesized ")" ""))
           )
     #{
       \tempo \markup {
         \line \general-align #Y #DOWN {
           % 1st column in line
           $label

           % 2nd column in line

           $left-paren

           \score {
             \new Staff \with {
               % reduce the font size a la cue
               fontSize = #tempoRelationshipStaffReduce
               \override StaffSymbol.staff-space = #(magstep tempoRelationshipStaffReduce)
               % hide the staff lines
               \override StaffSymbol.line-count = #0
               % align horizontally
               \override VerticalAxisGroup.Y-extent = #'(-0.85 . 0)
             }

             {
               % \override Score.SpacingSpanner.common-shortest-duration = #(ly:make-moment 1/2) % super-tight
               % \override Score.SpacingSpanner.common-shortest-duration = #(ly:make-moment 1/4) % tight
               % \override Score.SpacingSpanner.common-shortest-duration = #(ly:make-moment 3/16) % even
               \override Score.SpacingSpanner.common-shortest-duration = #(ly:make-moment 5/32) % even

               % the left music
               \relative c' { \stemUp $musicI }

               % the equivalence sign
               \once \override Score.TextScript.Y-offset = #-0.4
               s4.^\markup{
                 \halign #-1 "="
               }

               % the right music
               \relative c' { \stemUp $musicII }
             }

             \layout {
               indent = 0
               \context {
                 \Staff
                 \remove "Clef_engraver"
                 \remove "Time_signature_engraver"
               }
             } % layout end
           } % score end

           $right-paren

         } % line end
       } % markup end
     #}))
)!";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme function '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBook::addDampMarkupToScore ()
{
  string
    schemeFunctionName =
      "dampMarkup",

    schemeFunctionDescription =
R"(
% A function to create damp markups,
)",

    schemeFunctionCode =
      // add ! before ( and after ) since the code contains )"
R"!(
damp = \markup {
%  \scale #'(5 . 5)
  {
    \center-column {
      {
        \override #'(thickness . 1.8)
        \combine \draw-line #'(-1.5 . 0)
        \combine \draw-line #'(0 . -1.5)
        \combine \draw-line #'(0 . 1.5)
        \combine \draw-line #'(1.5 . 0)
        \draw-circle #0.8 #0.2 ##f
      }
    }
  }

}
)!";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme function '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBook::addDampAllMarkupToScore ()
{
  string
    schemeFunctionName =
      "dampAllMarkup",

    schemeFunctionDescription =
R"(
% A function to create damp all markups,
)",

    schemeFunctionCode =
      // add ! before ( and after ) since the code contains )"
R"!(
dampAll = \markup
%% do not use 'fontsize
%\scale #'(5 . 5)
{
  \combine \bold "O"
  \path #0.2
  #'((moveto -.4 .8)(lineto 2.2 .8)
      (closepath)
      (moveto .9 -.5)(lineto .9 2.1))
}
)!";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme function '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

void lpsrBook::addWhiteNoteHeadsToScore ()
{
  string
    schemeFunctionName =
      "whiteNoteHeads",

    schemeFunctionDescription =
R"(
% A function to display note shorter than a quarter with white heads,
% as in some ancient music scores
)",

    schemeFunctionCode =
      // add ! before ( and after ) since the code contains )"
R"!(
whiteNoteHeads =
#(define-music-function (music) (ly:music?)
   #{
     \temporary \override NoteHead.stencil = #ly:text-interface::print
     \temporary \override NoteHead.text = \markup {
       \musicglyph "noteheads.s1"
     }
     \omit \time 3/4
     \shiftDurations #1 #0 { #music }
     \omit \time 3/2
     \revert NoteHead.stencil
     \revert NoteHead.text
   #}
   )
)!";

  if (gLpsrOptions->fTraceSchemeFunctions) {
    gLogIOstream <<
      "Creating Scheme function '" << schemeFunctionName << "'" <<
      endl;
  }

  // create the Scheme function
  S_lpsrSchemeFunction
    schemeFunction =
      lpsrSchemeFunction::create (
        1, // inputLineNumber, JMI ???
        schemeFunctionName,
        schemeFunctionDescription,
        schemeFunctionCode);

  // register it in the Scheme functions map
  fScoreSchemeFunctionsMap [schemeFunctionName] =
    schemeFunction;
}

/* JMI
void lpsrBook::appendVoiceUseToStoreCommand (S_msrVoice voice)
{
  S_lpsrUseVoiceCommand
    useVoiceCommand =
      lpsrUseVoiceCommand::create (
        fInputLineNumber,
        voice);

  fScoreBlock->
    appendVoiceUseToParallelMusicBLock (useVoiceCommand);
}

void lpsrBook::appendLyricsUseToStoreCommand (S_msrStanza stanza)
{
  S_lpsrNewLyricsBlock
    newLyricsCommand =
      lpsrNewLyricsBlock::create (
        fInputLineNumber,
        stanza,
        stanza->getStanzaVoiceUplink ());

  fScoreBlock->
    appendLyricsUseToParallelMusicBLock (newLyricsCommand);
}
*/

void lpsrBook::acceptIn (basevisitor* v)
{
  if (gLpsrOptions->fTraceLpsrVisitors) {
    gLogIOstream <<
      "% ==> lpsrBook::acceptIn ()" <<
      endl;
  }

  if (visitor<S_lpsrBook>*
    p =
      dynamic_cast<visitor<S_lpsrBook>*> (v)) {
        S_lpsrBook elem = this;

        if (gLpsrOptions->fTraceLpsrVisitors) {
          gLogIOstream <<
            "% ==> Launching lpsrBook::visitStart ()" <<
            endl;
        }
        p->visitStart (elem);
  }
}

void lpsrBook::acceptOut (basevisitor* v)
{
  if (gLpsrOptions->fTraceLpsrVisitors) {
    gLogIOstream <<
      "% ==> lpsrBook::acceptOut ()" <<
      endl;
  }

  if (visitor<S_lpsrBook>*
    p =
      dynamic_cast<visitor<S_lpsrBook>*> (v)) {
        S_lpsrBook elem = this;

        if (gLpsrOptions->fTraceLpsrVisitors) {
          gLogIOstream <<
            "% ==> Launching lpsrBook::visitEnd ()" <<
            endl;
        }
        p->visitEnd (elem);
  }
}

void lpsrBook::browseData (basevisitor* v)
{
  if (gLpsrOptions->fTraceLpsrVisitors) {
    gLogIOstream <<
      "% ==> lpsrBook::browseData ()" <<
      endl;
  }

  {
    // browse the score LilyPond version
    msrBrowser<lpsrVarValAssoc> browser (v);
    browser.browse (*fLilypondVersion);
  }

  if (fInputSourceNameComment) {
    // browse the input source name comment
    msrBrowser<lpsrComment> browser (v);
    browser.browse (*fInputSourceNameComment);
  }

  if (fTranslationDateComment) {
    // browse the translation date comment
    msrBrowser<lpsrComment> browser (v);
    browser.browse (*fTranslationDateComment);
  }

  if (fCommandLineLongOptionsComment) {
    // browse the command line long options comment
    msrBrowser<lpsrComment> browser (v);
    browser.browse (*fCommandLineLongOptionsComment);
  }

  if (fCommandLineShortOptionsComment) {
    // browse the command line short options comment
    msrBrowser<lpsrComment> browser (v);
    browser.browse (*fCommandLineShortOptionsComment);
  }

  {
    // browse the score global size
    msrBrowser<lpsrSchemeVariable> browser (v);
    browser.browse (*fGlobalStaffSizeAssoc);
  }

  {
    // browse the Scheme function map
    for (
      map<string, S_lpsrSchemeFunction>::const_iterator i =
        fScoreSchemeFunctionsMap.begin ();
      i != fScoreSchemeFunctionsMap.end ();
      i++) {
      // browse the Scheme function
      msrBrowser<lpsrSchemeFunction> browser (v);
      browser.browse (*(*i).second);
    } // for
  }

  {
    // browse the score header
    msrBrowser<lpsrHeader> browser (v);
    browser.browse (*fHeader);
  }

  {
    // browse the score paper
    msrBrowser<lpsrPaper> browser (v);
    browser.browse (*fPaper);
  }

  {
    // browse the score layout
    msrBrowser<lpsrLayout> browser (v);
    browser.browse (*fScoreLayout);
  }

  {
    // browse the myBreakIsBreak assoc
    msrBrowser<lpsrVarValAssoc> browser (v);
    browser.browse (*fMyBreakIsBreakAssoc);
  }
  {
    // browse the myBreakIsEmpty assoc
    msrBrowser<lpsrVarValAssoc> browser (v);
    browser.browse (*fMyBreakIsEmptyAssoc);
  }

  {
    // browse the myPageBreakIsPageBreak assoc
    msrBrowser<lpsrVarValAssoc> browser (v);
    browser.browse (*fMyPageBreakIsPageBreakAssoc);
  }
  {
    // browse the myPageBreakIsEmpty assoc
    msrBrowser<lpsrVarValAssoc> browser (v);
    browser.browse (*fMyPageBreakIsEmptyAssoc);
  }

  if (fGlobalAssoc) {
    // browse the 'global' assoc
    msrBrowser<lpsrVarValAssoc> browser (v);
    browser.browse (*fGlobalAssoc);
  }

  {
    // browse the voices and stanzas list
    for (
      list<S_msrElement>::const_iterator i = fScoreElements.begin ();
      i != fScoreElements.end ();
      i++) {
      // browse the element
      msrBrowser<msrElement> browser (v);
      browser.browse (*(*i));
    } // for
  }

  {
    // browse the score command
    msrBrowser<lpsrBookBlock> browser (v);
    browser.browse (*fScoreBlock);
  }

  if (gLpsrOptions->fTraceLpsrVisitors) {
    gLogIOstream <<
      "% <== lpsrBook::browseData ()" <<
      endl;
  }
}

void lpsrBook::print (ostream& os)
{
  os <<
    "LPSR Score" <<
    endl <<
    endl;

  gIndenter++;

  // print the MSR structure (without the voices)
  fMsrScore->
    printSummary (os);
  os <<
    endl;

  // are some Scheme functions needed?
  const int fieldWidth = 42;

  os << left <<
    setw (fieldWidth) <<
    "TongueSchemeFunctionIsNeeded" << " : " <<
    booleanAsString (
      fTongueSchemeFunctionIsNeeded) <<
    endl <<
    setw (fieldWidth) <<
    "EditorialAccidentalSchemeFunctionIsNeeded" << " : " <<
    booleanAsString (
      fEditorialAccidentalSchemeFunctionIsNeeded) <<
    endl <<
    endl;

  // print LPSR basic information
  os <<
    fLilypondVersion <<
    endl <<

    fGlobalStaffSizeAssoc <<
    endl <<

    fHeader <<
    // no endl here

    fPaper <<
    endl <<

    fScoreLayout <<
    endl;

// myBreakAssoc,myPageBreakAssoc globalAssoc? JMI

  // print the voices
  if (fScoreElements.size ()) {
    list<S_msrElement>::const_iterator
      iBegin = fScoreElements.begin (),
      iEnd   = fScoreElements.end (),
      i      = iBegin;
    for ( ; ; ) {
      os << (*i);
      if (++i == iEnd) break;
      os << endl;
    } // for

    os <<
      endl;
  }

  // print the score block
  os <<
    fScoreBlock;

  gIndenter--;
}

ostream& operator<< (ostream& os, const S_lpsrBook& scr)
{
  scr->print (os);
  return os;
}


}
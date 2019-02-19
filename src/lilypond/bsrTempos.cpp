/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#include <iostream>
#include <sstream>
#include <regex>

#include "bsrMutualDependencies.h"

#include "messagesHandling.h"

#include "generalOptions.h"
#include "bsrOptions.h"


using namespace std;

namespace MusicXML2
{

//______________________________________________________________________________
S_bsrTempo bsrTempo::create (
  int        inputLineNumber,
  S_msrTempo mTempo)
{
  bsrTempo* o =
    new bsrTempo (
      inputLineNumber, mTempo);
  assert (o!=0);
  return o;
}

bsrTempo::bsrTempo (
  int        inputLineNumber,
  S_msrTempo mTempo)
    : bsrLineElement (inputLineNumber)
{
  fMsrTempo  = mTempo;

  fTempoCellsList = buildCellsList ();
}

bsrTempo::~bsrTempo ()
{}

S_bsrCellsList bsrTempo::buildCellsList () const
{
  S_bsrCellsList
    result =
      bsrCellsList::create (
        fInputLineNumber, kCellWordSign);

  switch (fMsrTempo->getTempoKind ()) {
    case msrTempo::k_NoTempoKind:
      break;
      
    case msrTempo::kTempoBeatUnitsPerMinute:
      {
        // fetch MSR tempo attributes
        const list<S_msrWords>&
          tempoWordsList =
            fMsrTempo->getTempoWordsList ();
  
        msrDottedDuration
          tempoDottedDuration =
            fMsrTempo->getTempoBeatUnit ();

        // handle tempo words
        int tempoWordsListSize = tempoWordsList.size ();
  
        if (tempoWordsListSize) {
          list<S_msrWords>::const_iterator
            iBegin = tempoWordsList.begin (),
            iEnd   = tempoWordsList.end (),
            i      = iBegin;
            
          for ( ; ; ) {
            S_msrWords words = (*i);
      
//            fLilypondCodeIOstream <<
   //           "\"" << words->getWordsContents () << "\"";
              
            if (++i == iEnd) break;
            
     //       fLilypondCodeIOstream <<
     //         " ";
          } // for
        }

        // handle tempo duration and continuation dots number
        msrDurationKind
          durationKind =
            tempoDottedDuration.getDurationKind ();
        int
          dotsNumber =
            tempoDottedDuration.getDotsNumber ();

        // determine the note sign
        bsrNote::bsrNoteValueKind
          noteValueKind = bsrNote::kNoteValueNone;

        switch (durationKind) {
          case k_NoDuration:
            break;
      
          case k1024th:
            break;
          case k512th:
            break;
          case k256th:
            noteValueKind = bsrNote::kNoteValueC256th;
            break;
          case k128th:
            noteValueKind = bsrNote::kNoteValueC128th;
            break;
          case k64th:
            noteValueKind = bsrNote::kNoteValueC64th;
            break;
          case k32nd:
            noteValueKind = bsrNote::kNoteValueC32nd;
            break;
          case k16th:
            noteValueKind = bsrNote::kNoteValueC16th;
            break;
          case kEighth:
            noteValueKind = bsrNote::kNoteValueC8th;
            break;
          case kQuarter:
            noteValueKind = bsrNote::kNoteValueCQuarter;
            break;
          case kHalf:
            noteValueKind = bsrNote::kNoteValueCHalf;
            break;
          case kWhole:
            noteValueKind = bsrNote::kNoteValueCWhole;
            break;
          case kBreve:
            noteValueKind = bsrNote::kNoteValueCBreve;
            break;
          case kLong:
            break;
          case kMaxima:
            break;
        } // switch

        // create a note to represent the duration
        S_bsrNote
          bNote =
            bsrNote::create (
              fInputLineNumber,
              noteValueKind,
              dotsNumber,
              bsrNote::kNoteOctaveNone,
              bsrNote::kNoteOctaveIsNeededNo,
              bsrNote::kNoteAccidentalNone);

        // append its cells to result
        result->
          appendCellsListToCellsList (
            bNote->fetchCellsList ());

        // append an equals to result
        result->
          appendCellKindToCellsList (
            kCellTempoEquals);

        // handle per minute value
        string
          tempoPerMinuteString =
            fMsrTempo->getTempoPerMinute ();

        int
          perMinuteMin = -1,
          perMinuteMax = -1; // may be absent
          
        // decipher it to extract min and max values
        string regularExpression (
          "[[:space:]]*([[:digit:]]+)[[:space:]]*"
          "-"
          "[[:space:]]*([[:digit:]]+)[[:space:]]*");
          
        regex e (regularExpression);
        smatch sm;
  
        regex_match (tempoPerMinuteString, sm, e);
  
        if (sm.size ()) {
  #ifdef TRACE_OPTIONS
          if (gGeneralOptions->fTraceOptions && ! gGeneralOptions->fQuiet) {
            gLogIOstream <<
              "There are " << sm.size () << " matches" <<
              " for rational string '" << tempoPerMinuteString <<
              "' with regex '" << regularExpression <<
              "'" <<
              endl;
         
            for (unsigned i = 0; i < sm.size (); ++i) {
              gLogIOstream <<
                "[" << sm [i] << "] ";
            } // for
            
            gLogIOstream <<
              endl;
          }
  #endif

          {
            stringstream s;
            s << sm [1];
            s >> perMinuteMin;
          }
          {
            stringstream s;
            s << sm [2];
            s >> perMinuteMax;
          }
        }
       
        else {
          perMinuteMin = stoi (tempoPerMinuteString);
        }
  
        // create a number to represent perMinuteMin
        S_bsrNumber
          perMinuteNumber =
            bsrNumber::create (
              fInputLineNumber,
              perMinuteMin,
              bsrNumber::kNumberSignIsNeededYes);

        // append its cells to result
        result->
          appendCellsListToCellsList (
            perMinuteNumber->getNumberCellsList ());

        if (perMinuteMax > 0) {
          // append a hyphen to result
          result->
            appendCellKindToCellsList (
              kCellTempoHyphen);
          
          // create a number to represent perMinuteMax
          S_bsrNumber
            perMinuteNumber =
              bsrNumber::create (
                fInputLineNumber,
                perMinuteMax,
                bsrNumber::kNumberSignIsNeededYes);

          // append a
          // append its cells to result
          result->
            appendCellsListToCellsList (
              perMinuteNumber->getNumberCellsList ());
        }
      }
      break;
      
    case msrTempo::kTempoBeatUnitsEquivalence:
      break;
      
    case msrTempo::kTempoNotesRelationShip:
      break;
  } // switch
  
  return result;
}

int bsrTempo::fetchCellsNumber() const
{
  return fTempoCellsList->fetchCellsNumber();
}

void bsrTempo::acceptIn (basevisitor* v)
{
#ifdef TRACE_OPTIONS
  if (gBsrOptions->fTraceBsrVisitors) {
    gLogIOstream <<
      "% ==> bsrTempo::acceptIn ()" <<
      endl;
  }
#endif
      
  if (visitor<S_bsrTempo>*
    p =
      dynamic_cast<visitor<S_bsrTempo>*> (v)) {
        S_bsrTempo elem = this;
        
#ifdef TRACE_OPTIONS
        if (gBsrOptions->fTraceBsrVisitors) {
          gLogIOstream <<
            "% ==> Launching bsrTempo::visitStart ()" <<
            endl;
        }
#endif
        p->visitStart (elem);
  }
}

void bsrTempo::acceptOut (basevisitor* v)
{
#ifdef TRACE_OPTIONS
  if (gBsrOptions->fTraceBsrVisitors) {
    gLogIOstream <<
      "% ==> bsrTempo::acceptOut ()" <<
      endl;
  }
#endif

  if (visitor<S_bsrTempo>*
    p =
      dynamic_cast<visitor<S_bsrTempo>*> (v)) {
        S_bsrTempo elem = this;
      
#ifdef TRACE_OPTIONS
        if (gBsrOptions->fTraceBsrVisitors) {
          gLogIOstream <<
            "% ==> Launching bsrTempo::visitEnd ()" <<
            endl;
        }
#endif
        p->visitEnd (elem);
  }
}

void bsrTempo::browseData (basevisitor* v)
{}

string bsrTempo::asString () const
{
  stringstream s;

  s <<
    "Tempo" << 
    ", tempoKind: " <<
    msrTempo::tempoKindAsString (fMsrTempo->getTempoKind ()) <<
    ", tempoCellsList: " <<
    fTempoCellsList->asShortString () <<
    ", spacesBefore: " << fSpacesBefore <<
    ", line " << fInputLineNumber;

  return s.str ();
}

void bsrTempo::print (ostream& os)
{
  os <<
    "Tempo" << 
    ", line " << fInputLineNumber <<
    endl;

  gIndenter++;

  const int fieldWidth = 23;

  os <<
    setw (fieldWidth) <<
    "tempoKind" << " : " <<
    msrTempo::tempoKindAsString (fMsrTempo->getTempoKind ()) <<
    endl <<
    setw (fieldWidth) <<
    "tempoCellsList" << " : " <<
    fTempoCellsList->asShortString () <<
    endl <<
    setw (fieldWidth) <<
    "spacesBefore" << " : " << fSpacesBefore <<
    endl;
        
  gIndenter--;
}

ostream& operator<< (ostream& os, const S_bsrTempo& elt)
{
  elt->print (os);
  return os;
}


}
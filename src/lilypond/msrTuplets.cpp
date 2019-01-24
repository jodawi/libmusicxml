/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#include "msrMutualDependencies.h"

#include "msrOptions.h"


using namespace std;

namespace MusicXML2 
{

//______________________________________________________________________________
S_msrTuplet msrTuplet::create (
  int                     inputLineNumber,
  string                  tupletMeasureNumber,
  int                     tupletNumber,
  msrTupletBracketKind    tupletBracketKind,
  msrTupletLineShapeKind  tupletLineShapeKind,
  msrTupletShowNumberKind tupletShowNumberKind,
  msrTupletShowTypeKind   tupletShowTypeKind,
  msrTupletFactor         tupletFactor,
  /*
  int                     tupletActualNotes,
  int                     tupletNormalNotes,
  */
  rational                memberNotesSoundingWholeNotes,
  rational                memberNotesDisplayWholeNotes,
  rational                notePositionInMeasure)
{
  msrTuplet* o =
    new msrTuplet (
      inputLineNumber,
      tupletMeasureNumber,
      tupletNumber,
      tupletBracketKind,
      tupletLineShapeKind,
      tupletShowNumberKind,
      tupletShowTypeKind,
      tupletFactor,
      /*
      tupletActualNotes,
      tupletNormalNotes,
      */
      memberNotesSoundingWholeNotes,
      memberNotesDisplayWholeNotes,
      notePositionInMeasure);
  assert(o!=0);
  return o;
}

msrTuplet::msrTuplet (
  int                     inputLineNumber,
  string                  tupletMeasureNumber,
  int                     tupletNumber,
  msrTupletBracketKind    tupletBracketKind,
  msrTupletLineShapeKind  tupletLineShapeKind,
  msrTupletShowNumberKind tupletShowNumberKind,
  msrTupletShowTypeKind   tupletShowTypeKind,
  msrTupletFactor         tupletFactor,
  /*
  int                     tupletActualNotes,
  int                     tupletNormalNotes,
  */
  rational                memberNotesSoundingWholeNotes,
  rational                memberNotesDisplayWholeNotes,
  rational                notePositionInMeasure)
    : msrMeasureElement (inputLineNumber)
{
  fTupletMeasureNumber = tupletMeasureNumber;
  
  fTupletNumber = tupletNumber;
  
  fTupletBracketKind    = tupletBracketKind;
  fTupletLineShapeKind  = tupletLineShapeKind;
  fTupletShowNumberKind = tupletShowNumberKind;
  fTupletShowTypeKind   = tupletShowTypeKind;

  fTupletFactor = tupletFactor;
//  fTupletActualNotes = tupletActualNotes;
//  fTupletNormalNotes = tupletNormalNotes;

  fMemberNotesSoundingWholeNotes = memberNotesSoundingWholeNotes;
  fMemberNotesDisplayWholeNotes  = memberNotesDisplayWholeNotes;
  
  fTupletSoundingWholeNotes = rational (0, 1);
  fTupletDisplayWholeNotes  = rational (0, 1);

  fTupletPositionInMeasure = notePositionInMeasure;
}

msrTuplet::~msrTuplet ()
{}

S_msrTuplet msrTuplet::createTupletNewbornClone ()
{
#ifdef TRACE_OPTIONS
  if (gGeneralOptions->fTraceTuplets) {
    gLogIOstream <<
      "Creating a newborn clone of tuplet '" <<
      asString () <<
      "'" <<
      endl;
  }
#endif

  S_msrTuplet
    newbornClone =
      msrTuplet::create (
        fInputLineNumber,
        fTupletMeasureNumber,
        fTupletNumber,
        fTupletBracketKind,
        fTupletLineShapeKind,
        fTupletShowNumberKind,
        fTupletShowTypeKind,
        fTupletFactor,
      //  fTupletActualNotes = tupletActualNotes;
      //  fTupletNormalNotes = tupletNormalNotes;
        fMemberNotesSoundingWholeNotes,
        fMemberNotesDisplayWholeNotes,
        fTupletPositionInMeasure);

  newbornClone->fTupletSoundingWholeNotes =
    fTupletSoundingWholeNotes;

  newbornClone->fTupletDisplayWholeNotes =
    fTupletDisplayWholeNotes;

  newbornClone->fTupletMeasureNumber =
    fTupletMeasureNumber;

  return newbornClone;
}

string msrTuplet::tupletTypeKindAsString (
  msrTupletTypeKind tupletTypeKind)
{
  string result;

  switch (tupletTypeKind) {
    case msrTuplet::kTupletTypeNone:
      result = "tupletTypeNone";
      break;
    case msrTuplet::kTupletTypeStart:
      result = "tupletTypeStart";
      break;
    case msrTuplet::kTupletTypeContinue:
      result = "tupletTypeContinue";
      break;
    case msrTuplet::kTupletTypeStop:
      result = "tupletTypeStop";
      break;
    case msrTuplet::kTupletTypeStartAndStopInARow:
      result = "tupletTypeStartAndStopInARow";
      break;
  } // switch

  return result;
}

string msrTuplet::tupletBracketKindAsString (
  msrTupletBracketKind tupletBracketKind)
{
  string result;

  switch (tupletBracketKind) {
    case msrTuplet::kTupletBracketYes:
      result = "tupletBracketYes";
      break;
    case msrTuplet::kTupletBracketNo:
      result = "tupletBracketNo";
      break;
  } // switch

  return result;
}

string msrTuplet::tupletLineShapeKindAsString (
  msrTupletLineShapeKind tupletLineShapeKind)
{
  string result;

  switch (tupletLineShapeKind) {
    case msrTuplet::kTupletLineShapeStraight:
      result = "tupletLineShapeStraight";
      break;
    case msrTuplet::kTupletLineShapeCurved:
      result = "tupletLineShapeCurved";
      break;
  } // switch

  return result;
}

string msrTuplet::tupletShowNumberKindAsString (
  msrTupletShowNumberKind tupletShowNumberKind)
{
  string result;
  
  switch (tupletShowNumberKind) {
    case msrTuplet::kTupletShowNumberActual:
      result = "tupletShowNumberActual";
      break;
    case msrTuplet::kTupletShowNumberBoth:
      result = "tupletShowNumberBoth";
      break;
    case msrTuplet::kTupletShowNumberNone:
      result = "tupletShowNumberNone";
      break;
  } // switch

  return result;
}

string msrTuplet::tupletShowTypeKindAsString (
  msrTupletShowTypeKind tupletShowTypeKind)
{
  string result;
  
  switch (tupletShowTypeKind) {
    case msrTuplet::kTupletShowTypeActual:
      result = "tupletShowTypeActual";
      break;
    case msrTuplet::kTupletShowTypeBoth:
      result = "tupletShowTypeBoth";
      break;
    case msrTuplet::kTupletShowTypeNone:
      result = "tupletShowTypeNone";
      break;
  } // switch

  return result;
}
      
void msrTuplet::addNoteToTuplet (
  S_msrNote  note,
  S_msrVoice voice)
{
#ifdef TRACE_OPTIONS
  if (gGeneralOptions->fTraceTuplets) {
    gLogIOstream <<
      "Adding note '" <<
      note->asShortString () <<
      // the information is missing to display it the normal way
      "' to tuplet '" <<
      asString () <<
      "'" <<
      endl;
  }
#endif

  fTupletElementsList.push_back (note);

  // register note's tuplet uplink
  note->
    setNoteTupletUplink (this);

  // account for note duration
  fTupletSoundingWholeNotes +=
    note->getNoteSoundingWholeNotes ();
  fTupletSoundingWholeNotes.rationalise ();
  
  fTupletDisplayWholeNotes += // JMI
    note->getNoteDisplayWholeNotes ();  
  fTupletDisplayWholeNotes.rationalise ();
      
  // populate note's position in measure
  note->setNotePositionInMeasure (
    fTupletPositionInMeasure);
}

void msrTuplet::addChordToTuplet (S_msrChord chord)
{
#ifdef TRACE_OPTIONS
  if (gGeneralOptions->fTraceChords || gGeneralOptions->fTraceTuplets) {
    gLogIOstream <<
      "Adding chord '" <<
      chord->asString () <<
      "' to tuplet '" <<
      asString () <<
      "'" <<
      endl;
  }
#endif

  fTupletElementsList.push_back (chord);
    
  // account for chord duration
  fTupletSoundingWholeNotes +=
    chord->getChordSoundingWholeNotes ();
  fTupletSoundingWholeNotes.rationalise ();

  fTupletDisplayWholeNotes += // JMI
    chord->getChordDisplayWholeNotes ();  
  fTupletDisplayWholeNotes.rationalise ();
    
  // populate chord's measure number
  chord->setChordMeasureNumber (
    fTupletMeasureNumber);

  // populate chord's position in measure
  chord->setChordPositionInMeasure (
    fTupletPositionInMeasure);
}

void msrTuplet::addTupletToTuplet (S_msrTuplet tuplet)
{
#ifdef TRACE_OPTIONS
  if (gGeneralOptions->fTraceTuplets) {
    gLogIOstream <<
      "Adding tuplet '" <<
      tuplet->asString () <<
      "' to tuplet '" <<
      asString () <<
      "'" <<
      endl;
  }
#endif

/* JMI
  // unapply containing tuplet factor,
  // i.e 3/2 inside 5/4 becomes 15/8 in MusicXML...
  tuplet->
    unapplySoundingFactorToTupletMembers (
      this->fTupletActualNotes,
      this->fTupletNormalNotes);
  */
  
  // register tuplet in elements list
  fTupletElementsList.push_back (tuplet);
    
  // account for tuplet duration
  fTupletSoundingWholeNotes +=
    tuplet->getTupletSoundingWholeNotes ();
  fTupletSoundingWholeNotes.rationalise ();

  fTupletDisplayWholeNotes += // JMI
    tuplet->getTupletDisplayWholeNotes ();
  fTupletDisplayWholeNotes.rationalise ();
    
    /*
  fTupletDisplayWholeNotes += // JMI
    tuplet->getTupletDisplayWholeNotes ();  
    */

  // don't populate tuplet's position in measure,
  // this will be done in setTupletMeasureNumber () JMI ???
  /* JMI
  // populate tuplet's position in measure
  tuplet->setTupletPositionInMeasure (
    fTupletPositionInMeasure);
    */
}

void msrTuplet::addTupletToTupletClone (S_msrTuplet tuplet)
{
#ifdef TRACE_OPTIONS
  if (gGeneralOptions->fTraceTuplets) {
    gLogIOstream <<
      "Adding tuplet '" <<
      tuplet->asString () <<
      "' to tuplet '" <<
      asString () <<
      "'" <<
      endl;
  }
#endif

  // dont' unapply containing tuplet factor,
  // this has been done when building the MSR from MusicXML
  
  // register tuplet in elements list
  fTupletElementsList.push_back (tuplet);
    
  // account for tuplet duration
  fTupletSoundingWholeNotes +=
    tuplet->getTupletSoundingWholeNotes ();
  fTupletSoundingWholeNotes.rationalise ();

  fTupletDisplayWholeNotes +=
    tuplet->getTupletDisplayWholeNotes ();
  fTupletDisplayWholeNotes.rationalise ();
}

S_msrNote msrTuplet::fetchTupletFirstNonGraceNote () const
{
  S_msrNote result;

  if (fTupletElementsList.size ()) {
    S_msrElement
      firstTupletElement =
        fTupletElementsList.front ();

    if (
      S_msrNote note = dynamic_cast<msrNote*>(&(*firstTupletElement))
      ) {
      // first element is a note, we have it
      result = note;
    }
    
    else if (
      S_msrTuplet tuplet = dynamic_cast<msrTuplet*>(&(*firstTupletElement))
      ) {
      // first element is another tuplet, recurse
      result = tuplet->fetchTupletFirstNonGraceNote ();
    }
  }
  
  else {
    msrInternalError (
      gGeneralOptions->fInputSourceName,
      fInputLineNumber,
      __FILE__, __LINE__,
      "cannot access the first note of an empty tuplet");
  }

  return result;
}

S_msrNote msrTuplet::removeFirstNoteFromTuplet (
  int       inputLineNumber)
{
  S_msrNote result;
  
#ifdef TRACE_OPTIONS
  if (gGeneralOptions->fTraceTuplets) {
    gLogIOstream <<
      "Removing first note from tuplet '" <<
      asString () <<
      "'" <<
      endl;
  }
#endif

  if (fTupletElementsList.size ()) {
    S_msrElement
      firstTupletElement =
        fTupletElementsList.front ();

    if (
      S_msrNote note = dynamic_cast<msrNote*>(&(*firstTupletElement))
      ) {
      fTupletElementsList.pop_front ();
      result = note;
    }
    
    else {
      if (true) {
        this->print (gLogIOstream);
      }
      
      msrInternalError (
        gGeneralOptions->fInputSourceName,
        fInputLineNumber,
        __FILE__, __LINE__,
        "removeFirstNoteFromTuplet () expects a note as the first tuplet element");
    }

/* JMI
    for (
      list<S_msrElement>::iterator i=fTupletElementsList.begin ();
      i!=fTupletElementsList.end ();
      ++i) {
      if ((*i) == note) {
        // found note, erase it
        fTupletElementsList.erase (i);
        
        // account for note duration
        fTupletSoundingWholeNotes -=
          note->getNoteSoundingWholeNotes ();
        fTupletSoundingWholeNotes.rationalise ();

        fTupletDisplayWholeNotes -= // JMI
          note->getNoteDisplayWholeNotes ();  
        fTupletDisplayWholeNotes.rationalise ();

        // don't update measure number nor position in measure: // JMI
        // they have not been set yet
  
        // return from function
        return;
      }
    } // for

    stringstream s;

    s <<
      "cannot remove note " <<
      note <<
      " from tuplet " << asString () <<
      "' in voice \"" <<
      fTupletMeasureUplink->
        getMeasureSegmentUplink ()->
          getSegmentVoiceUplink ()->
            getVoiceName () <<
      "\"," <<
      " since it has not been found";

    msrInternalError (
      gGeneralOptions->fInputSourceName,
      inputLineNumber,
      __FILE__, __LINE__,
      s.str ());
  */
  }
  
  else {
    stringstream s;

    s <<
      "cannot remove the first note of an empty tuplet " <<
      "' in voice \"" <<
      fTupletMeasureUplink->
        getMeasureSegmentUplink ()->
          getSegmentVoiceUplink ()->
            getVoiceName () <<
      "\"";

    msrInternalError (
      gGeneralOptions->fInputSourceName,
      inputLineNumber,
      __FILE__, __LINE__,
      s.str ());
  }

  return result;
}

S_msrNote msrTuplet::removeLastNoteFromTuplet (
  int       inputLineNumber)
{
  S_msrNote result;
  
#ifdef TRACE_OPTIONS
  if (gGeneralOptions->fTraceTuplets) {
    gLogIOstream <<
      "Removing last note from tuplet '" <<
      asString () <<
      "'" <<
      endl;
  }
#endif

  if (fTupletElementsList.size ()) {
    S_msrElement
      lastTupletElement =
        fTupletElementsList.back ();

    if (
      S_msrNote note = dynamic_cast<msrNote*>(&(*lastTupletElement))
      ) {
      fTupletElementsList.pop_back ();
      result = note;
    }
    
    else {
      if (true) {
        this->print (gLogIOstream);
      }
      
      msrInternalError (
        gGeneralOptions->fInputSourceName,
        fInputLineNumber,
        __FILE__, __LINE__,
        "removeLastNoteFromTuplet () expects a note as the last tuplet element");
    }
  }
  
  else {
    stringstream s;

    s <<
      "cannot remove the last note of an empty tuplet " <<
      "' in voice \"" <<
      fTupletMeasureUplink->
        getMeasureSegmentUplink ()->
          getSegmentVoiceUplink ()->
            getVoiceName () <<
      "\"";

    msrInternalError (
      gGeneralOptions->fInputSourceName,
      inputLineNumber,
      __FILE__, __LINE__,
      s.str ());
  }

#ifdef TRACE_OPTIONS
  if (gGeneralOptions->fTraceNotes || gGeneralOptions->fTraceGraceNotes) {
    gLogIOstream <<
      "This last note from grace notes '" <<
      asString () <<
      "' turns out to be '" <<
      result->asShortString () <<
      "'" <<
      endl;
  }
#endif

  return result;
}

void msrTuplet::setTupletMeasureNumber (string measureNumber)
{
  fTupletMeasureNumber = measureNumber;
}

rational msrTuplet::setTupletPositionInMeasure (
  rational positionInMeasure)
  // returns the position in measure after the tuplet
{
  fTupletPositionInMeasure = positionInMeasure;

  rational currentPosition = positionInMeasure;
  
  // compute position in measure for the tuplets elements
  for (
    list<S_msrElement>::const_iterator i = fTupletElementsList.begin ();
    i != fTupletElementsList.end ();
    i++ ) {
    // set tuplet element position in measure
    
    if (
      S_msrNote note = dynamic_cast<msrNote*>(&(*(*i)))
      ) {    
      note->
        setNotePositionInMeasure (currentPosition);
        
      currentPosition +=
        note->
          getNoteSoundingWholeNotes ();
    }
  
    else if (
      S_msrChord chord = dynamic_cast<msrChord*>(&(*(*i)))
      ) {
      chord->
        setChordPositionInMeasure (currentPosition);
        
      currentPosition +=
        chord->
          getChordSoundingWholeNotes ();
    }
    
    else if (
      S_msrTuplet tuplet = dynamic_cast<msrTuplet*>(&(*(*i)))
      ) {
      currentPosition =
        tuplet->
          setTupletPositionInMeasure (currentPosition);
    }
    
    else {
      msrInternalError (
        gGeneralOptions->fInputSourceName,
        fInputLineNumber,
        __FILE__, __LINE__,
        "tuplet member should be a note, a chord or another tuplet");
    }

  } // for

  return currentPosition;
}

void msrTuplet::unapplySoundingFactorToTupletMembers (
  const msrTupletFactor& containingTupletFactor)
  /*
  int containingTupletActualNotes,
  int containingTupletNormalNotes)
  */
{
#ifdef TRACE_OPTIONS
  if (gGeneralOptions->fTraceTuplets) {
    gLogIOstream <<
      "unapplySoundingFactorToTupletMembers ()" <<
      endl;

    gIndenter++;
    
    gLogIOstream <<
      "% fTupletFactor = " << fTupletFactor.asString () <<
      /*
      "% fTupletActualNotes = " <<
      fTupletActualNotes <<
      ", fTupletNormalNotes = " <<
      fTupletNormalNotes <<
      */
      endl <<
      "% containingTupletFactor = " << containingTupletFactor.asString () <<
      /*
      "% containingTupletActualNotes = " <<
      containingTupletActualNotes <<
      ", containingTupletNormalNotes = " <<
      containingTupletNormalNotes <<
      */
      endl <<
      endl;

    gIndenter--;
  }
#endif

  fTupletFactor.fTupletActualNotes /=
    containingTupletFactor.fTupletActualNotes;
  fTupletFactor.fTupletNormalNotes /=
    containingTupletFactor.fTupletNormalNotes;

    /*
  fTupletActualNotes /=
    containingTupletActualNotes;
  fTupletNormalNotes /=
    containingTupletNormalNotes;
    */
}

void msrTuplet::acceptIn (basevisitor* v)
{
  if (gMsrOptions->fTraceMsrVisitors) {
    gLogIOstream <<
      "% ==> msrTuplet::acceptIn ()" <<
      endl;
  }
      
  if (visitor<S_msrTuplet>*
    p =
      dynamic_cast<visitor<S_msrTuplet>*> (v)) {
        S_msrTuplet elem = this;
        
        if (gMsrOptions->fTraceMsrVisitors) {
          gLogIOstream <<
            "% ==> Launching msrTuplet::visitStart ()" <<
            endl;
        }
        p->visitStart (elem);
  }
}

void msrTuplet::acceptOut (basevisitor* v)
{
  if (gMsrOptions->fTraceMsrVisitors) {
    gLogIOstream <<
      "% ==> msrTuplet::acceptOut ()" <<
      endl;
  }

  if (visitor<S_msrTuplet>*
    p =
      dynamic_cast<visitor<S_msrTuplet>*> (v)) {
        S_msrTuplet elem = this;
      
        if (gMsrOptions->fTraceMsrVisitors) {
          gLogIOstream <<
            "% ==> Launching msrTuplet::visitEnd ()" <<
            endl;
        }
        p->visitEnd (elem);
  }
}

void msrTuplet::browseData (basevisitor* v)
{
  for (
    list<S_msrElement>::const_iterator i = fTupletElementsList.begin ();
    i != fTupletElementsList.end ();
    i++ ) {
    // browse tuplet element
    msrBrowser<msrElement> browser (v);
    browser.browse (*(*i));
  } // for
}

string msrTuplet::asString () const
{
  stringstream s;

  s <<
    "Tuplet " <<
    fTupletFactor.asString () <<
    " " << fTupletSoundingWholeNotes << " tupletSoundingWholeNotes" <<
    " @meas "<<
    fTupletMeasureNumber <<
    ":";

  if (fTupletPositionInMeasure.getNumerator () < 0) {
    s << "?";
  }
  else {
    s << fTupletPositionInMeasure;
  }
  
  s << "[[";

  if (fTupletElementsList.size ()) {
    list<S_msrElement>::const_iterator
      iBegin = fTupletElementsList.begin (),
      iEnd   = fTupletElementsList.end (),
      i      = iBegin;
    for ( ; ; ) {
      
      if (
        S_msrNote note = dynamic_cast<msrNote*>(&(*(*i)))
        ) {    
        s <<
          note->asShortString ();
      }
    
      else if (
        S_msrChord chord = dynamic_cast<msrChord*>(&(*(*i)))
        ) {
        s <<
          chord->asString ();
      }
      
      else if (
        S_msrTuplet tuplet = dynamic_cast<msrTuplet*>(&(*(*i)))
        ) {
        s <<
          tuplet->asString ();
      }
      
      else {
        msrInternalError (
          gGeneralOptions->fInputSourceName,
          fInputLineNumber,
          __FILE__, __LINE__,
          "tuplet member should be a note, a chord or another tuplet");
      }
  
      if (++i == iEnd) break;
      s << " ";
      
    } // for
  }

  s << "]]";
  
  return s.str ();
}

void msrTuplet::print (ostream& os)
{
  os <<
    "Tuplet " <<
    fTupletFactor.asString () <<
    ", " <<
    singularOrPlural (
      fTupletElementsList.size (), "element", "elements") <<
    ", whole notes: " <<
    fTupletSoundingWholeNotes << " sounding, " <<
    fTupletDisplayWholeNotes << " displayed" <<
    ", meas "<<
    fTupletMeasureNumber <<
    ", line " << fInputLineNumber <<
    endl;

  gIndenter++;
  
  const int fieldWidth = 30;

  os << left <<
    setw (fieldWidth) <<
    "TupletBracketKind" << " : " <<
    tupletBracketKindAsString (
      fTupletBracketKind) <<
    endl <<
    setw (fieldWidth) <<
    "TupletLineShapeKind" << " : " <<
    tupletLineShapeKindAsString (
      fTupletLineShapeKind) <<
    endl <<
    setw (fieldWidth) <<
    "TupletShowNumberKind" << " : " <<
    tupletShowNumberKindAsString (
      fTupletShowNumberKind) <<
    endl <<
    setw (fieldWidth) <<
    "TupletShowTypeKind" << " : " <<
    tupletShowTypeKindAsString (
      fTupletShowTypeKind) <<
    endl <<
    setw (fieldWidth) <<
    "MemberNotesSoundingWholeNotes" << " : " <<
    fMemberNotesSoundingWholeNotes <<
    endl <<
    setw (fieldWidth) <<
    "MemberNotesDisplayWholeNotes" << " : " <<
    fMemberNotesDisplayWholeNotes <<
    endl <<
    endl;

/* JMI ???
  os << left <<
    setw (fieldWidth) <<
    "(position in measure" << " : ";
  if (fTupletPositionInMeasure.getNumerator () < 0) {
    os << "???)";
  }
  else {
    os << fTupletPositionInMeasure << ")";
  }
  os <<
    endl;
    */

  gIndenter--;

  if (fTupletElementsList.size ()) {
    gIndenter++;

    list<S_msrElement>::const_iterator
      iBegin = fTupletElementsList.begin (),
      iEnd   = fTupletElementsList.end (),
      i      = iBegin;
    for ( ; ; ) {
      os << (*i);
      if (++i == iEnd) break;
      os << endl;
    } // for
    
    gIndenter--;
    
  // JMI  os << endl;
  }
}

void msrTuplet::printShort (ostream& os)
{
  os <<
    "Tuplet " <<
    fTupletFactor.asString () <<
    ", " <<
    singularOrPlural (
      fTupletElementsList.size (), "element", "elements") <<
    ", whole notes: " <<
    fTupletSoundingWholeNotes << " sounding, " <<
    fTupletDisplayWholeNotes << " displayed" <<
    ", meas "<<
    fTupletMeasureNumber <<
    ", line " << fInputLineNumber <<
    endl;

  gIndenter++;
  
  const int fieldWidth = 30;

  os << left <<
    setw (fieldWidth) <<
    "TupletBracketKind" << " : " <<
    tupletBracketKindAsString (
      fTupletBracketKind) <<
    endl <<
    setw (fieldWidth) <<
    "TupletLineShapeKind" << " : " <<
    tupletLineShapeKindAsString (
      fTupletLineShapeKind) <<
    endl <<
    setw (fieldWidth) <<
    "TupletShowNumberKind" << " : " <<
    tupletShowNumberKindAsString (
      fTupletShowNumberKind) <<
    endl <<
    setw (fieldWidth) <<
    "TupletShowTypeKind" << " : " <<
    tupletShowTypeKindAsString (
      fTupletShowTypeKind) <<
    endl <<
    setw (fieldWidth) <<
    "MemberNotesSoundingWholeNotes" << " : " <<
    fMemberNotesSoundingWholeNotes <<
    endl <<
    setw (fieldWidth) <<
    "MemberNotesDisplayWholeNotes" << " : " <<
    fMemberNotesDisplayWholeNotes <<
    endl <<
    endl;

/* JMI ???
  os << left <<
    setw (fieldWidth) <<
    "(position in measure" << " : ";
  if (fTupletPositionInMeasure.getNumerator () < 0) {
    os << "???)";
  }
  else {
    os << fTupletPositionInMeasure << ")";
  }
  os <<
    endl;
    */

  gIndenter--;

  if (fTupletElementsList.size ()) {
    os <<
      "TupletElements:" <<
      endl;
      
    gIndenter++;

    list<S_msrElement>::const_iterator
      iBegin = fTupletElementsList.begin (),
      iEnd   = fTupletElementsList.end (),
      i      = iBegin;
    for ( ; ; ) {
      os <<
        (*i)->asShortString () <<
        endl;
      if (++i == iEnd) break;
      os << endl;
    } // for
    
    gIndenter--;
    
  // JMI  os << endl;
  }
}

ostream& operator<< (ostream& os, const S_msrTuplet& elt)
{
  elt->print (os);
  return os;
}


}

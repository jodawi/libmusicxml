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
S_msrGraceNotesGroup msrGraceNotesGroup::create (
  int                    inputLineNumber,
  msrGraceNotesGroupKind graceNotesGroupKind,
  bool                   graceNotesGroupIsSlashed,
  S_msrVoice             graceNotesGroupVoiceUplink)
{
  msrGraceNotesGroup* o =
    new msrGraceNotesGroup (
      inputLineNumber,
      graceNotesGroupKind,
      graceNotesGroupIsSlashed,
      graceNotesGroupVoiceUplink);
  assert(o!=0);

  return o;
}

msrGraceNotesGroup::msrGraceNotesGroup (
  int                    inputLineNumber,
  msrGraceNotesGroupKind graceNotesGroupKind,
  bool                   graceNotesGroupIsSlashed,
  S_msrVoice             graceNotesGroupVoiceUplink)
    : msrElement (inputLineNumber)
{
  // sanity check
  msrAssert(
    graceNotesGroupVoiceUplink != nullptr,
    "graceNotesGroupVoiceUplink is null");

  fGraceNotesGroupVoiceUplink =
    graceNotesGroupVoiceUplink;    

  fGraceNotesGroupKind = graceNotesGroupKind;
  
  fGraceNotesGroupIsSlashed = graceNotesGroupIsSlashed;

  fGraceNotesGroupIsTied = false;

  // grace notes are followed by notes
  // unless they are last in a measure
  fGraceNotesGroupIsFollowedByNotes = true;
}

msrGraceNotesGroup::~msrGraceNotesGroup ()
{}

S_msrGraceNotesGroup msrGraceNotesGroup::createGraceNotesGroupNewbornClone (
  S_msrVoice containingVoice)
{
#ifdef TRACE_OPTIONS
  if (gGeneralOptions->fTraceGraceNotes) {
    gLogIOstream <<
      "Creating a newborn clone of grace notes group '" <<
      asShortString () <<
      "'" <<
      endl;
  }
#endif
  
  // sanity check
  msrAssert(
    containingVoice != nullptr,
    "containingVoice is null");
    
  S_msrGraceNotesGroup
    newbornClone =
      msrGraceNotesGroup::create (
        fInputLineNumber,
        fGraceNotesGroupKind,
        fGraceNotesGroupIsSlashed,
        containingVoice);

  newbornClone->fGraceNotesGroupIsTied =
    fGraceNotesGroupIsTied;
    
  newbornClone->fGraceNotesGroupIsFollowedByNotes =
    fGraceNotesGroupIsFollowedByNotes;
    
  return newbornClone;
}

S_msrPart msrGraceNotesGroup::fetchGraceNotesGroupPartUplink () const
{
  return
    fGraceNotesGroupVoiceUplink->
      fetchVoicePartUplink ();
}

string msrGraceNotesGroup::graceNotesGroupKindAsString (
  msrGraceNotesGroupKind graceNotesGroupKind)
{
  string result;
  
  switch (graceNotesGroupKind) {
    case msrGraceNotesGroup::kGraceNotesGroupBefore:
      result = "graceNotesGroupBefore";
      break;
    case msrGraceNotesGroup::kGraceNotesGroupAfter:
      result = "graceNotesGroupAfter";
      break;
  } // switch

  return result;
}

S_msrGraceNotesGroup msrGraceNotesGroup::createSkipGraceNotesGroupClone (
  S_msrVoice containingVoice)
{
#ifdef TRACE_OPTIONS
  if (gGeneralOptions->fTraceGraceNotes) {
    gLogIOstream <<
      "Creating a skip clone of grace notes group '" <<
      asShortString () <<
      "'" <<
      endl;
  }
#endif

  // sanity check
  msrAssert (
    containingVoice != nullptr,
    "containingVoice is null");

  // create the grace notes group
  S_msrGraceNotesGroup
    clone =
      msrGraceNotesGroup::create (
        fInputLineNumber,
        fGraceNotesGroupKind,
        fGraceNotesGroupIsSlashed,
        containingVoice);

  clone->fGraceNotesGroupIsTied =
    fGraceNotesGroupIsTied;
    
  clone->fGraceNotesGroupIsFollowedByNotes =
    fGraceNotesGroupIsFollowedByNotes;
    
  // populating the clone with skips
  for (
    list<S_msrElement>::const_iterator i=fGraceNotesGroupElementsList.begin ();
    i!=fGraceNotesGroupElementsList.end ();
    i++) {      
    if (
      S_msrNote note = dynamic_cast<msrNote*>(&(*(*i)))
    ) {
      // create skip with same duration as note
      S_msrNote
        skip =
          msrNote::createSkipNote (
            note->            getInputLineNumber (),
            note->            getNoteMeasureNumber (),
            note->            getNoteDisplayWholeNotes (), // would be 0/1 otherwise JMI
            note->            getNoteDisplayWholeNotes (),
            note->            getNoteDotsNumber (),
            containingVoice-> getRegularVoiceStaffSequentialNumber (), // JMI
            containingVoice-> getVoiceNumber ());

      // append it to the grace notes
      clone->
        appendNoteToGraceNotesGroup (skip);
    }
  
    else if (
      S_msrChord chord = dynamic_cast<msrChord*>(&(*(*i)))
    ) {
      // fetch the chord's first note
      S_msrNote
        chordFirstNote =
          chord->getChordNotesVector () [0];

      // create skip with same duration as chord
      S_msrNote
        skip =
          msrNote::createSkipNote (
            chordFirstNote->  getInputLineNumber (),
            chordFirstNote->  getNoteMeasureNumber (),
            chordFirstNote->  getNoteDisplayWholeNotes (), // would be 0/1 otherwise JMI
            chordFirstNote->  getNoteDisplayWholeNotes (),
            chordFirstNote->  getNoteDotsNumber (),
            containingVoice-> getRegularVoiceStaffSequentialNumber (), // JMI
            containingVoice-> getVoiceNumber ());

      // append it to the grace notes
      clone->
        appendNoteToGraceNotesGroup (skip);
    }
    
    else {
      msrInternalError (
        gGeneralOptions->fInputSourceName,
        fInputLineNumber,
        __FILE__, __LINE__,
        "grace notes element should be a note or a chord");
    }    
  } // for
    
  return clone;
}

void msrGraceNotesGroup::appendNoteToGraceNotesGroup (S_msrNote note)
{
#ifdef TRACE_OPTIONS
  if (gGeneralOptions->fTraceGraceNotes || gGeneralOptions->fTraceGraceNotes) {
    gLogIOstream <<
      "Appending note '" <<
      note->asShortString () <<
      "' to grace notes group" <<
      asShortString () <<
      " in voice \"" <<
      fGraceNotesGroupVoiceUplink->getVoiceName () <<
      "\"" <<
      endl;
  }
#endif

  fGraceNotesGroupElementsList.push_back (note);

  // register note's grace notes groups uplink
  note->
    setNoteGraceNotesGroupUplink (this);

  // is this grace note tied?
  if (note->getNoteTie ()) {
    fGraceNotesGroupIsTied = true;
  }
}

void msrGraceNotesGroup::appendChordToGraceNotesGroup (S_msrChord chord)
{
#ifdef TRACE_OPTIONS
  if (gGeneralOptions->fTraceChords || gGeneralOptions->fTraceGraceNotes) {
    gLogIOstream <<
      "Appending chord '" <<
      chord->asShortString () <<
      "' to grace notes group '" <<
      asShortString () <<
      "' in voice \"" <<
      fGraceNotesGroupVoiceUplink->getVoiceName () <<
      "\"" <<
      endl;
  }
#endif

  fGraceNotesGroupElementsList.push_back (chord);
}

S_msrNote msrGraceNotesGroup::removeLastNoteFromGraceNotesGroup (
  int inputLineNumber)
{
#ifdef TRACE_OPTIONS
  if (gGeneralOptions->fTraceGraceNotes || gGeneralOptions->fTraceGraceNotes) {
    gLogIOstream <<
      "Removing last note from grace notes group '" <<
      asShortString () <<
      "' in voice \"" <<
      fGraceNotesGroupVoiceUplink->getVoiceName () <<
      "\"" <<
      endl;
  }
#endif

  // sanity check
  msrAssert (
    fGraceNotesGroupElementsList.size () != 0,
    "fGraceNotesGroupElementsList.size () == 0");

#ifdef TRACE_OPTIONS
  if (gGeneralOptions->fTraceNotes || gGeneralOptions->fTraceGraceNotes) {
    gLogIOstream <<
      "Removing last note from grace notes '" <<
      asString () <<
      "'" <<
      endl;
  }
#endif

  S_msrNote result;

  if (
    S_msrNote note = dynamic_cast<msrNote*>(&(*fGraceNotesGroupElementsList.back ()))
    ) {
    result = note;
  }

  else {
    msrInternalError (
      gGeneralOptions->fInputSourceName,
      fInputLineNumber,
      __FILE__, __LINE__,
      "removeLastNoteFromGraceNotesGroup (): grace notes group element should be a note");
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

  fGraceNotesGroupElementsList.pop_back ();

  return result;
}

void msrGraceNotesGroup::acceptIn (basevisitor* v)
{
  if (gMsrOptions->fTraceMsrVisitors) {
    gLogIOstream <<
      "% ==> msrGraceNotesGroup::acceptIn ()" <<
      endl;
  }
      
  if (visitor<S_msrGraceNotesGroup>*
    p =
      dynamic_cast<visitor<S_msrGraceNotesGroup>*> (v)) {
        S_msrGraceNotesGroup elem = this;
        
        if (gMsrOptions->fTraceMsrVisitors) {
          gLogIOstream <<
            "% ==> Launching msrGraceNotesGroup::visitStart ()" <<
            endl;
        }
        p->visitStart (elem);
  }
}

void msrGraceNotesGroup::acceptOut (basevisitor* v)
{
  if (gMsrOptions->fTraceMsrVisitors) {
    gLogIOstream <<
      "% ==> msrGraceNotesGroup::acceptOut ()" <<
      endl;
  }

  if (visitor<S_msrGraceNotesGroup>*
    p =
      dynamic_cast<visitor<S_msrGraceNotesGroup>*> (v)) {
        S_msrGraceNotesGroup elem = this;
      
        if (gMsrOptions->fTraceMsrVisitors) {
          gLogIOstream <<
            "% ==> Launching msrGraceNotesGroup::visitEnd ()" <<
            endl;
        }
        p->visitEnd (elem);
  }
}

void msrGraceNotesGroup::browseData (basevisitor* v)
{
  list<S_msrElement>::const_iterator i;

  for (
    i=fGraceNotesGroupElementsList.begin ();
    i!=fGraceNotesGroupElementsList.end ();
    i++) {
    // browse the element (note or chord)
    msrBrowser<msrElement> browser (v);
    browser.browse (*(*i));
  } // for
}

string msrGraceNotesGroup::asShortString () const
{
  stringstream s;

  s <<
    "GraceNotesGroup" <<
    ", graceNotesGroupKind \"" <<
    graceNotesGroupKindAsString (
      fGraceNotesGroupKind) <<
    ", graceNotesGroupMeasureNumber \"" << fGraceNotesGroupMeasureNumber <<
    "\", line " << fInputLineNumber << " ";

  if (fGraceNotesGroupElementsList.size ()) {
    list<S_msrElement>::const_iterator
      iBegin = fGraceNotesGroupElementsList.begin (),
      iEnd   = fGraceNotesGroupElementsList.end (),
      i      = iBegin;
    for ( ; ; ) {
      s << (*i)->asShortString ();
      if (++i == iEnd) break;
      s << ", ";
    } // for
  }
  
  return s.str ();
}

string msrGraceNotesGroup::asString () const
{
  stringstream s;

  s <<
    "GraceNotesGroup" <<
    ", graceNotesGroupMeasureNumber \"" << fGraceNotesGroupMeasureNumber <<
    ", graceNotesGroupMeasureNumber \"" << fGraceNotesGroupMeasureNumber <<
    "\", line " << fInputLineNumber << " ";

  if (fGraceNotesGroupElementsList.size ()) {
    list<S_msrElement>::const_iterator
      iBegin = fGraceNotesGroupElementsList.begin (),
      iEnd   = fGraceNotesGroupElementsList.end (),
      i      = iBegin;
    for ( ; ; ) {
      s << (*i)->asString ();
      if (++i == iEnd) break;
      s << ", ";
    } // for
  }
  
  return s.str ();
}

void msrGraceNotesGroup::print (ostream& os)
{
  os <<
    "GraceNotesGroup" <<
    ", line " << fInputLineNumber <<
    ", " <<
    singularOrPlural (
      fGraceNotesGroupElementsList.size (), "element", "elements") <<
    endl;

  gIndenter++;

  const int fieldWidth = 33;
  
  os <<
    setw (fieldWidth) <<
    "graceNotesGroupVoiceUplink" << " : ";
    if (fGraceNotesGroupVoiceUplink) {
      os <<
        fGraceNotesGroupVoiceUplink->asShortString ();
    }
    else {
      os <<
        "none";
    }
  os <<
    endl;
    
  os <<
    setw (fieldWidth) <<
    "graceNotesGroupNoteUplink" << " : ";
    if (fGraceNotesGroupNoteUplink) {
      os <<
        fGraceNotesGroupNoteUplink->asShortString ();
    }
    else {
      os <<
        "none";
    }
  os <<
    endl;
    
  os <<
    setw (fieldWidth) <<
    "graceNotesGroupIsSlashed" << " : " <<
    booleanAsString (fGraceNotesGroupIsSlashed) <<
    endl <<
    
    setw (fieldWidth) <<
    "graceNotesGroupIsSlashed" << " : " <<
    booleanAsString (fGraceNotesGroupIsSlashed) <<
    endl <<
    
    setw (fieldWidth) <<
    "graceNotesGroupIsTied" << " : " <<
    booleanAsString (fGraceNotesGroupIsTied) <<
    endl <<
    
    setw (fieldWidth) <<
    "graceNotesGroupIsFollowedByNotes" << " : " <<
    booleanAsString (fGraceNotesGroupIsFollowedByNotes) <<
    endl <<
    
    setw (fieldWidth) <<
    "graceNotesGroupMeasureNumber" << " : " <<
    fGraceNotesGroupMeasureNumber <<
    endl;
  
  os <<
    setw (fieldWidth) <<
    "graceNotesGroupElementsList";
  if (fGraceNotesGroupElementsList.size ()) {
    os <<
      endl;
      
    gIndenter++;
  
    list<S_msrElement>::const_iterator
      iBegin = fGraceNotesGroupElementsList.begin (),
      iEnd   = fGraceNotesGroupElementsList.end (),
      i      = iBegin;
      
    for ( ; ; ) {
      os << (*i);
      if (++i == iEnd) break;
      os << endl;
    } // for
  
    gIndenter--;
  }
  else {
    os <<
       " : " <<
       "none" <<
      endl;
  }

  gIndenter--;
}

ostream& operator<< (ostream& os, const S_msrGraceNotesGroup& elt)
{
  elt->print (os);
  return os;
}


}

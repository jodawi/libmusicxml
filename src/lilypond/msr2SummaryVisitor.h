/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#ifndef __msr2SummaryVisitor__
#define __msr2SummaryVisitor__

#include <map>
#include <vector>

#include "msr.h"

#include "musicxml2msr.h"

namespace MusicXML2
{

/*!
\addtogroup visitors
@{
*/

/*!
\brief Produces a summary of a MusicXML part.

  A part summary consists in 
  - a number of staves
  - a map that associates each stave with the corresponding number of notes
  - a map that associates each stave with the corresponding voices and notes
  - a map that associates each stave with the correcponding lyricss
*/
class msr2SummaryVisitor :

  public visitor<S_msrScore>,
  
  public visitor<S_msrPartgroup>,
  
  public visitor<S_msrPart>,
  
  public visitor<S_msrStaff>,
  
  public visitor<S_msrVoice>,

  public visitor<S_msrLyrics>,
  public visitor<S_msrLyricsChunk>,
  
  public visitor<S_msrClef>,
  public visitor<S_msrKey>,
  public visitor<S_msrTime>,
  public visitor<S_msrTempo>,
  
  public visitor<S_msrSequentialMusic>,
  public visitor<S_msrParallelMusic>,
  
  public visitor<S_msrDuration>,
  
  public visitor<S_msrArticulation>,

  public visitor<S_msrDynamics>,
  public visitor<S_msrWedge>,
  
  public visitor<S_msrNote>,
  public visitor<S_msrBeam>,
    
  public visitor<S_msrChord>,
  
  public visitor<S_msrTuplet>,
  
  public visitor<S_msrSlur>,
  
  public visitor<S_msrBarLine>,
  public visitor<S_msrBarNumberCheck>,
  public visitor<S_msrBreak>,
  
  public visitor<S_msrRepeat>,
  
  public visitor<S_msrComment>,
  
  public visitor<S_msrVarValAssoc>,
  
  public visitor<S_msrHeader>,
  public visitor<S_msrPaper>,
  public visitor<S_msrLayout>,
  
  public visitor<S_msrMidi>

{
  public:
  
    msr2SummaryVisitor (
      S_msrOptions& msrOpts,
      ostream&      os);
        
    virtual ~msr2SummaryVisitor ();

    void printSummaryFromMsrScore (
      const S_msrScore& score);
    
  protected:
      
    virtual void visitStart (S_msrScore& elt);
    virtual void visitEnd   (S_msrScore& elt);

    virtual void visitStart (S_msrPartgroup& elt);
    virtual void visitEnd   (S_msrPartgroup& elt);

    virtual void visitStart (S_msrPart& elt);
    virtual void visitEnd   (S_msrPart& elt);

    virtual void visitStart (S_msrStaff& elt);
    virtual void visitEnd   (S_msrStaff& elt);

    virtual void visitStart (S_msrVoice& elt);
    virtual void visitEnd   (S_msrVoice& elt);

    virtual void visitStart (S_msrLyrics& elt);
    virtual void visitEnd   (S_msrLyrics& elt);

    virtual void visitStart (S_msrLyricsChunk& elt);
    virtual void visitEnd   (S_msrLyricsChunk& elt);

    virtual void visitStart (S_msrClef& elt);
    virtual void visitEnd   (S_msrClef& elt);

    virtual void visitStart (S_msrKey& elt);
    virtual void visitEnd   (S_msrKey& elt);

    virtual void visitStart (S_msrTime& elt);
    virtual void visitEnd   (S_msrTime& elt);

    virtual void visitStart (S_msrTempo& elt);
    virtual void visitEnd   (S_msrTempo& elt);

    virtual void visitStart (S_msrSequentialMusic& elt);
    virtual void visitEnd   (S_msrSequentialMusic& elt);

    virtual void visitStart (S_msrParallelMusic& elt);
    virtual void visitEnd   (S_msrParallelMusic& elt);

    virtual void visitStart (S_msrDuration& elt);
    virtual void visitEnd   (S_msrDuration& elt);

    virtual void visitStart (S_msrArticulation& elt);
    virtual void visitEnd   (S_msrArticulation& elt);

    virtual void visitStart (S_msrDynamics& elt);
    virtual void visitEnd   (S_msrDynamics& elt);

    virtual void visitStart (S_msrWedge& elt);
    virtual void visitEnd   (S_msrWedge& elt);

    virtual void visitStart (S_msrNote& elt);
    virtual void visitEnd   (S_msrNote& elt);

    virtual void visitStart (S_msrBeam& elt);
    virtual void visitEnd   (S_msrBeam& elt);

    virtual void visitStart (S_msrChord& elt);
    virtual void visitEnd   (S_msrChord& elt);

    virtual void visitStart (S_msrTuplet& elt);
    virtual void visitEnd   (S_msrTuplet& elt);

    virtual void visitStart (S_msrSlur& elt);
    virtual void visitEnd   (S_msrSlur& elt);

    virtual void visitStart (S_msrBarLine& elt);
    virtual void visitEnd   (S_msrBarLine& elt);

    virtual void visitStart (S_msrBarNumberCheck& elt);
    virtual void visitEnd   (S_msrBarNumberCheck& elt);

    virtual void visitStart (S_msrBreak& elt);
    virtual void visitEnd   (S_msrBreak& elt);

    virtual void visitStart (S_msrRepeat& elt);
    virtual void visitEnd   (S_msrRepeat& elt);

    virtual void visitStart (S_msrComment& elt);
    virtual void visitEnd   (S_msrComment& elt);

    virtual void visitStart (S_msrVarValAssoc& elt);
    virtual void visitEnd   (S_msrVarValAssoc& elt);

    virtual void visitStart (S_msrHeader& elt);
    virtual void visitEnd   (S_msrHeader& elt);

    virtual void visitStart (S_msrPaper& elt);
    virtual void visitEnd   (S_msrPaper& elt);

    virtual void visitStart (S_msrLayout& elt);
    virtual void visitEnd   (S_msrLayout& elt);

    virtual void visitStart (S_msrMidi& elt);
    virtual void visitEnd   (S_msrMidi& elt);

  private:
                     
    S_msrOptions   fMsrOptions;
    ostream&       fOstream;

    // score
    // ------------------------------------------------------
    int            fScoreStandaloneNotesCounter;
    int            fScoreRestNotesCounter;
    int            fScoreChordNotesCounter;
    int            fScoreTupletNotesCounter;
    int            fScoreChordsCounter;
    
    // part groups
    // ------------------------------------------------------

    // parts
    // ------------------------------------------------------

    // staves
    // ------------------------------------------------------
    // prevent clef, key and time from being printed twice
    bool           fOnGoingStaff;

    // voices
    // ------------------------------------------------------

    // lyrics
    // ------------------------------------------------------

    // chords
    // ------------------------------------------------------

    // tuplets
    // ------------------------------------------------------
};


/*! @} */

}

#endif

/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#include <sstream>

#include <climits>      /* INT_MIN, INT_MAX */
#include <iomanip>      // setw, set::precision, ...

#include "msrOptionsHandling.h"

#include "utilities.h"


using namespace std;

namespace MusicXML2 
{

// useful shortcut macros
#define idtr indenter::gIndenter
#define tab  indenter::gIndenter.getSpacer ()

//______________________________________________________________________________
msrOptionsElement::msrOptionsElement (
  string optionsElementShortName,
  string optionsElementLongName,
  string optionsElementDescription)
{
  fOptionsElementShortName   = optionsElementShortName;  
  fOptionsElementLongName    = optionsElementLongName;  
  fOptionsElementDescription = optionsElementDescription;  
}

msrOptionsElement::~msrOptionsElement()
{}

ostream& operator<< (ostream& os, const S_msrOptionsElement& elt)
{
  elt->print (os);
  return os;
}

void msrOptionsElement::print (ostream& os) const
{
  os << "??? msrOptionsElement ???" << endl;
}

//______________________________________________________________________________
msrOptionsItem::msrOptionsItem (
  string             optionsItemShortName,
  string             optionsItemLongName,
  string             optionsItemDescription,
  msrOptionsItemKind optionsItemKind)
  : msrOptionsElement (
      optionsItemShortName,
      optionsItemLongName,
      optionsItemDescription)
{
  fOptionsItemKind = optionsItemKind;
  
  fOptionsItemHasBeenSelected = false;
}
    
msrOptionsItem::~msrOptionsItem()
{}

string msrOptionsItem::optionsItemKindAsString (
  msrOptionsItem::msrOptionsItemKind optionsItemKind)
{
  string result;
  
  switch (optionsItemKind) {
    case msrOptionsItem::kOptionsItemHasNoArgument:
      result = "OptionsItemHasNoArgument";
      break;
    case msrOptionsItem::kOptionsItemHasARequiredArgument:
      result = "OptionsItemHasARequiredArgument";
      break;
    case msrOptionsItem::kOptionsItemHasAnOptionsArgument:
      result = "OptionsItemHasAnOptionsArgument";
      break;
  } // switch

  return result;
}  

void msrOptionsItem::print (ostream& os) const
{
  const int fieldWidth = 19;
  
  os <<
    "OptionsItem ???:" <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementShortName" << " : " << fOptionsElementShortName <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementLongName" << " : " << fOptionsElementLongName <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementDescription" << " : " << fOptionsElementDescription <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsItemKind" << " : " <<
      optionsItemKindAsString (
        fOptionsItemKind) <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsItemHasBeenSelected" << " : " <<
    booleanAsString (
      fOptionsItemHasBeenSelected) <<
    endl;
}

ostream& operator<< (ostream& os, const S_msrOptionsItem& elt)
{
  os <<
    "OptionsItem ???:" <<
    endl;
  elt->print (os);
  return os;
}

//______________________________________________________________________________
msrOptionsBoolItem::msrOptionsBoolItem (
  string optionsItemShortName,
  string optionsItemLongName,
  string optionsItemDescription,
  bool&  optionsBoolItemVariable)
  : msrOptionsItem (
      optionsItemShortName,
      optionsItemLongName,
      optionsItemDescription,
      msrOptionsItem::kOptionsItemHasNoArgument),
    fOptionsBoolItemVariable (optionsBoolItemVariable)
{}

msrOptionsBoolItem::~msrOptionsBoolItem()
{}

void msrOptionsBoolItem::print (ostream& os) const
{
  const int fieldWidth = 19;
  
  os <<
    "OptionsBoolItem:" <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementShortName" << " : " << fOptionsElementShortName <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementLongName" << " : " << fOptionsElementLongName <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementDescription" << " : " << fOptionsElementDescription <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsItemHasBeenSelected" << " : " <<
    booleanAsString (
      fOptionsItemHasBeenSelected) <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsBoolItemVariable" << " : " <<
    booleanAsString (
      fOptionsBoolItemVariable) <<
    endl;
}

ostream& operator<< (ostream& os, const S_msrOptionsBoolItem& elt)
{
  os <<
    "OptionsBoolItem:" <<
    endl;
  elt->print (os);
  return os;
}

//______________________________________________________________________________
msrOptionsIntItem::msrOptionsIntItem (
  string             optionsItemShortName,
  string             optionsItemLongName,
  string             optionsItemDescription,
  int&               optionsIntItemVariable,
  msrOptionsItemKind optionsItemKind)
  : msrOptionsItem (
      optionsItemShortName,
      optionsItemLongName,
      optionsItemDescription,
      optionsItemKind),
    fOptionsIntItemVariable (optionsIntItemVariable)
{}

msrOptionsIntItem::~msrOptionsIntItem()
{}

void msrOptionsIntItem::print (ostream& os) const
{
  const int fieldWidth = 19;
  
  os <<
    "OptionsIntItem:" <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementShortName" << " : " << fOptionsElementShortName <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementLongName" << " : " << fOptionsElementLongName <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementDescription" << " : " << fOptionsElementDescription <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsItemHasBeenSelected" << " : " <<
    booleanAsString (
      fOptionsItemHasBeenSelected) <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsIntItemVariable" << " : " << fOptionsIntItemVariable <<
    endl;
}

ostream& operator<< (ostream& os, const S_msrOptionsIntItem& elt)
{
  os <<
    "OptionsIntItem:" <<
    endl;
  elt->print (os);
  return os;
}

//______________________________________________________________________________
msrOptionsFloatItem::msrOptionsFloatItem (
  string             optionsItemShortName,
  string             optionsItemLongName,
  string             optionsItemDescription,
  float&             optionsFloatItemVariable,
  msrOptionsItemKind optionsItemKind)
  : msrOptionsItem (
      optionsItemShortName,
      optionsItemLongName,
      optionsItemDescription,
      optionsItemKind),
    fOptionsFloatItemVariable (optionsFloatItemVariable)
{}

msrOptionsFloatItem::~msrOptionsFloatItem()
{}

void msrOptionsFloatItem::print (ostream& os) const
{
  const int fieldWidth = 19;
  
  os <<
    "OptionsFloatItem:" <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementShortName" << " : " << fOptionsElementShortName <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementLongName" << " : " << fOptionsElementLongName <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementDescription" << " : " << fOptionsElementDescription <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsItemHasBeenSelected" << " : " <<
    booleanAsString (
      fOptionsItemHasBeenSelected) <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsFloatItemVariable" << " : " << fOptionsFloatItemVariable <<
    endl;
}

ostream& operator<< (ostream& os, const S_msrOptionsFloatItem& elt)
{
  os <<
    "OptionsFloatItem:" <<
    endl;
  elt->print (os);
  return os;
}

//______________________________________________________________________________
msrOptionsStringItem::msrOptionsStringItem (
  string             optionsItemShortName,
  string             optionsItemLongName,
  string             optionsItemDescription,
  string&            optionsStringItemVariable,
  msrOptionsItemKind optionsItemKind)
  : msrOptionsItem (
      optionsItemShortName,
      optionsItemLongName,
      optionsItemDescription,
      optionsItemKind),
    fOptionsStringItemVariable (optionsStringItemVariable)
{}

msrOptionsStringItem::~msrOptionsStringItem()
{}

void msrOptionsStringItem::print (ostream& os) const
{
  const int fieldWidth = 19;
  
  os <<
    "OptionsStringItem:" <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementShortName" << " : " << fOptionsElementShortName <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementLongName" << " : " << fOptionsElementLongName <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementDescription" << " : " << fOptionsElementDescription <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsItemHasBeenSelected" << " : " <<
    booleanAsString (
      fOptionsItemHasBeenSelected) <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsStringItemVariable" << " : " << fOptionsStringItemVariable <<
    endl;
}

ostream& operator<< (ostream& os, const S_msrOptionsStringItem& elt)
{
  os <<
    "OptionsStringItem:" <<
    endl;
  elt->print (os);
  return os;
}

//______________________________________________________________________________
msrOptionsRationalItem::msrOptionsRationalItem (
  string             optionsItemShortName,
  string             optionsItemLongName,
  string             optionsItemDescription,
  rational&          optionsRationalItemVariable,
  msrOptionsItemKind optionsItemKind)
  : msrOptionsItem (
      optionsItemShortName,
      optionsItemLongName,
      optionsItemDescription,
      optionsItemKind),
    fOptionsRationalItemVariable (optionsRationalItemVariable)
{}

msrOptionsRationalItem::~msrOptionsRationalItem()
{}

void msrOptionsRationalItem::print (ostream& os) const
{
  const int fieldWidth = 19;
  
  os <<
    "OptionsRationalItem:" <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementShortName" << " : " << fOptionsElementShortName <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementLongName" << " : " << fOptionsElementLongName <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementDescription" << " : " << fOptionsElementDescription <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsItemHasBeenSelected" << " : " <<
    booleanAsString (
      fOptionsItemHasBeenSelected) <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsRationalItemVariable" << " : " << fOptionsRationalItemVariable <<
    endl;
}

ostream& operator<< (ostream& os, const S_msrOptionsRationalItem& elt)
{
  os <<
    "OptionsRationalItem:" <<
    endl;
  elt->print (os);
  return os;
}

//______________________________________________________________________________
msrOptionsSubGroup::msrOptionsSubGroup (
  string optionsSubGroupShortName,
  string optionsSubGroupLongName,
  string optionsSubGroupDescription)
  : msrOptionsElement (
      optionsSubGroupShortName,
      optionsSubGroupLongName,
      optionsSubGroupDescription)
{}

msrOptionsSubGroup::~msrOptionsSubGroup()
{}

void msrOptionsSubGroup::print (ostream& os) const
{
  const int fieldWidth = 19;
  
  os <<
    "OptionsSubGroup:" <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementShortName" << " : " << fOptionsElementShortName <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementLongName" << " : " << fOptionsElementLongName <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementDescription" << " : " << fOptionsElementDescription <<
    endl;

  for (
    list<S_msrOptionsItem>::const_iterator
      i = fOptionsSubGroupItemsList.begin();
    i != fOptionsSubGroupItemsList.end();
    i++) {
    // print the element
    os << (*i);
  } // for
}

ostream& operator<< (ostream& os, const S_msrOptionsSubGroup& elt)
{
  os <<
    "OptionsSubGroup:" <<
    endl;
  elt->print (os);
  return os;
}

//______________________________________________________________________________
msrOptionsGroup::msrOptionsGroup (
  string optionGroupShortName,
  string optionGroupLongName,
  string optionGroupDescription)
  : msrOptionsElement (
      optionGroupShortName,
      optionGroupLongName,
      optionGroupDescription)
{}

msrOptionsGroup::~msrOptionsGroup()
{}

void msrOptionsGroup::print (ostream& os) const
{
  const int fieldWidth = 19;
  
  os <<
    "OptionsGroup:" <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementShortName" << " : " << fOptionsElementShortName <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementLongName" << " : " << fOptionsElementLongName <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementDescription" << " : " << fOptionsElementDescription <<
    endl;

  for (
    list<S_msrOptionsSubGroup>::const_iterator
      i = fOptionsGroupSubGroupsList.begin();
    i != fOptionsGroupSubGroupsList.end();
    i++) {
    // print the element
    os << (*i);
  } // for
}

ostream& operator<< (ostream& os, const S_msrOptionsGroup& elt)
{
  os <<
    "OptionsGroup:" <<
    endl;
  elt->print (os);
  return os;
}

//______________________________________________________________________________
msrOptionsGroupsList::msrOptionsGroupsList (
  string optionGroupsListShortName,
  string optionGroupsListLongName,
  string optionGroupsListDescription)
  : msrOptionsElement (
      optionGroupsListShortName,
      optionGroupsListLongName,
      optionGroupsListDescription)
{}

msrOptionsGroupsList::~msrOptionsGroupsList()
{}

void msrOptionsGroupsList::print (ostream& os) const
{
  const int fieldWidth = 19;
  
  os <<
    "OptionsGroupsList:" <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementShortName" << " : " << fOptionsElementShortName <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementLongName" << " : " << fOptionsElementLongName <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementDescription" << " : " << fOptionsElementDescription <<
    endl;

  for (
    list<S_msrOptionsGroup>::const_iterator
      i = fOptionsGroupGroupsList.begin();
    i != fOptionsGroupGroupsList.end();
    i++) {
    // print the element
    os << (*i);
  } // for
}

ostream& operator<< (ostream& os, const S_msrOptionsGroupsList& elt)
{
  os <<
    "OptionsGroupsList:" <<
    endl;
  elt->print (os);
  return os;
}

//______________________________________________________________________________
msrOptionsHandler::msrOptionsHandler (
  string optionHandlerShortName,
  string optionHandlerLongName,
  string optionHandlerDescription)
  : msrOptionsElement (
      optionHandlerShortName,
      optionHandlerLongName,
      optionHandlerDescription)
{}

msrOptionsHandler::~msrOptionsHandler()
{}

void msrOptionsHandler::checkOptionUniqueness (
  string optionLongName,
  string optionShortName)
{
  if (optionShortName == optionLongName) {
    stringstream s;

    s <<
      "option long name '" << optionLongName << "'" <<
      " is also used as short name";
      
    optionError (s.str());
  }
  
  for (
    map<string, string>::iterator i = fOptionShortNames.begin();
    i != fOptionShortNames.end();
    i++) {
      
    // is optionLongName in the options names map?
    if ((*i).first == optionLongName) {
      stringstream s;
  
      s <<
        "option long name '" << optionLongName << "'" <<
        " is specified more that once";
        
      optionError (s.str());
    }

    // is optionShortName in the options names map?
    if ((*i).second == optionShortName) {
      if (optionShortName.size ()) {
        stringstream s;
    
        s <<
          "option short name '" << optionShortName << "'" <<
          " for option long name '" << optionLongName << "'" <<
          " is specified more that once";
          
        optionError (s.str());
      }
    }
  } // for

  // everything OK, register the option names
  fOptionShortNames [optionLongName] = optionShortName;
}

void msrOptionsHandler::print (ostream& os) const
{
  const int fieldWidth = 19;
  
  os <<
    "OptionsHandler:" <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementShortName" << " : " << fOptionsElementShortName <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementLongName" << " : " << fOptionsElementLongName <<
    endl <<
    setw(fieldWidth) <<
    "fOptionsElementDescription" << " : " << fOptionsElementDescription <<
    endl;

  for (
    list<S_msrOptionsGroup>::const_iterator
      i = fOptionsGroupHandler.begin();
    i != fOptionsGroupHandler.end();
    i++) {
    // print the element
    os << (*i);
  } // for
}

ostream& operator<< (ostream& os, const S_msrOptionsHandler& elt)
{
  os <<
    "OptionsHandler:" <<
    endl;
  elt->print (os);
  return os;
}

/* JMI
  S_msrOptionsGroupsList optionsGroupsList =
    new msrOptionsGroupsList (
    "h", "help", " help for OptionsGroupsList");

  optionsGroupsList->
    appendOptionsGroup (optionsGroup);
    
  cerr <<
    optionsGroupsList <<
    endl;
    */

void msrOptionsHandler::analyzeOptions (
  int   argc,
  char* argv[])
{
  int   n = 0;

  while (true) { 
    if (argv [n] == 0)
      break;

    string currentElement = string (argv [n]);
    
    // print current element
    cout <<
      n << ":" << currentElement <<
      endl;

    // handle current element
    if (currentElement [0] == '-') {
      // this is an option
      string elementTrailer =
        currentElement.substr (1, string::npos);

      /* JMI
      cout <<
        "elementTrailer '" << elementTrailer << "' is preceded by a dash" <<
        endl;
      */

      if (elementTrailer.size ()) {
        if (elementTrailer [0] == '-') {
          // it is a double-dashed option
          string currentDoubleDashedOption =
            elementTrailer.substr (1, string::npos);
          
          cout <<
            "'" << currentDoubleDashedOption << "' is a double-dashed option" <<
            endl;
        }
        else {
          // it is a single-dashed option
          string currentSingleDashedOption =
            elementTrailer; //.substr (1, string::npos);
          
          cout <<
            "'" << currentSingleDashedOption << "' is a single-dashed option" <<
            endl;
        }
      }
      
      else {
        cout <<
          "'-' is the minimal single-dashed option" <<
          endl;
      }
    }

    // next please
    n++;
  } // while
}

//______________________________________________________________________________
void initializeOptionsHandling ()
{
}


}

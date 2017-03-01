//----------------------------------------------------------------------------
//
// "Copyright Centre National d'Etudes Spatiales"
//
// License:  LGPL
//
// See LICENSE.txt file in the top level directory for more details.
//
//----------------------------------------------------------------------------

#include "erssar/ErsSarRecordFactory.h"

namespace ossimplugins
{

ErsSarRecordFactory::ErsSarRecordFactory()
{
}

ErsSarRecordFactory::~ErsSarRecordFactory()
{
}

ErsSarRecord* ErsSarRecordFactory::Instantiate(int id)
{
  ErsSarRecord* record = _availableRecords[id];
  if (record == NULL)
  {
    return NULL;
  }
  else
  {
    return record->Instantiate();
  }
}

void ErsSarRecordFactory::RegisterRecord(int id, ErsSarRecord * record)
{
  _availableRecords[id] = record;
}
}

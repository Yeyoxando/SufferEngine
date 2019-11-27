/*
* Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
* Date: 27-11-2019
* System Header
*/

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "referenced.h"
#include "data_types.h"

namespace Suffer {

  class System : public virtual Referenced {

  public:
    explicit System() {}

  protected:
    virtual ~System();

  };

}
#endif // __SYSTEM_H__

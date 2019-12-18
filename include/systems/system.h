/*
* Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
* Date: 27-11-2019
* System Header
*/

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "referenced.h"
#include "data_types.h"
#include "game_object.h"

namespace Suffer {

  class System : public virtual Referenced {
    friend class SufferManager;
  public:
    explicit System() {}
	void DeactivateSystem(bool status);

  protected:

    virtual void Execute(GameObject* go);
    virtual ~System();

	bool active_;
	int id_;
  };

}
#endif // __SYSTEM_H__

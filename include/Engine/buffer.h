/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 11-06-2019
* Buffer Header (Material, Transform, Geometry)
*/

#ifndef __BUFFER_H__ 
#define __BUFFER_H__

#include <referenced.h>
#include <data_types.h>

enum BufferType {
    kBufferType_Vertex = 0,
    kBufferType_Indices,
    kBufferType_Invalid = 20
};

namespace Suffer {

    class Buffer : public Referenced {

    public:

        void Init();
        void GetVertex(u32 index);

    protected:
        Buffer();
        Buffer(const Buffer& b) = delete;
        virtual ~Buffer();

    private:

        u8 id_;

    };

}
#endif //__BUFFER_H__

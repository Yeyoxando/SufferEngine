/*
 * Author: Pablo Bano Benito <banyobe@esat-alumni.com>
 * Date: 10-14-2019
 * Referenced Header
 * Original Class by Jose L. Hidalgo
 */

#ifndef __REFERENCED_H__
#define __REFERENCED_H__

#include <data_types.h>
#include <assert.h>

namespace Suffer {

	class Referenced {

	public:
		void ref();
		void unref();

	protected:

		Referenced();
		virtual ~Referenced();

	private:

		u32 reference_counter_;
		Referenced(const Referenced&) = delete;

	};

	inline Referenced::Referenced() {
		reference_counter_ = 0;
	}

	inline Referenced::~Referenced() {

	}

	inline void Referenced::ref() {
		reference_counter_++;
	}

	inline void Referenced::unref() {
#ifdef ASSERT
		assert(reference_counter_ > 0);
#endif
		--reference_counter_;
		if (!reference_counter_) {
			delete this;
		}

	}

}
#endif // __REFERENCED_H__

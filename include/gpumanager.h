// Pablo Bano Benito <banyobe@esat-alumni.com>

#ifndef __GPU_MANAGER_H__
#define __GPU_MANAGER_H__

namespace Suffer {

	class GPUManager {

	public:

		static GPUManager& instance();

	protected:

		GPUManager();
		virtual ~GPUManager();

	private:

		GPUManager(const GPUManager&);

	};

}

#endif // __GPU_MANAGER_H__

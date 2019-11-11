// Pablo Bano Benito <banyobe@esat-alumni.com>

#ifndef __SUFFER_MANAGER_H__
#define __SUFFER_MANAGER_H__

#include <ref_ptr.h>
#include <render_manager.h>
#include <audio_manager.h>
#include <scoped_array.h>
#include <thread.h>
#include <material.h>
#include "vector2.h"

class Scene;

// --------------------------------------------------------------//

namespace Suffer {

	class SufferManager {

	public:
		friend class Audio3D;
		friend class Audio2D;
		friend class Interface;
		friend class DrawGeometry;

		static SufferManager& instance();

		bool Init();
		bool Run();
		bool Step(double time_step);
		bool Finish();

		double DeltaTime();

		// Resources

		class GPUResource : public Referenced {

		public:
			GPUResource();
			~GPUResource();

			enum ResourceType {
				kVertexBuffer = 0,
				kIndexBuffer,
				kFrameBuffer,
				kTexture,
				kInvalid
			};

			s32 id_;

			ResourceType type_;

		};

		class VertexBuffer : public GPUResource {
		public:
			friend class SufferManager;
			enum VertexFormat {
				kVertexFormat_3P = 0,
				kVertexFormat_3P_3N = 1,
				kVertexFormat_Invalid
			};

			VertexBuffer();
			~VertexBuffer() {};
      
			VertexFormat format_;

		};

		class IndexBuffer : public GPUResource {
		public:
			IndexBuffer();
			~IndexBuffer() {};

		};

		//Buffers
		void UploadVertexData(const ref_ptr<VertexBuffer> buffer, Array<float> *data);
		void UploadVertexData(const ref_ptr<VertexBuffer> buffer, float* data, u32 size);
		void UploadIndexData(const ref_ptr<IndexBuffer> buffer, Array<u16> *data);
		void UploadIndexData(const ref_ptr<IndexBuffer> buffer, u16* data, u32 size);

    mathmorra::Vector2 GetMousePosition();

		// Subsystems
    AudioManager audio_manager_;
		RenderManager render_manager_;

	protected:

		SufferManager();
		virtual ~SufferManager();

	private:

		SufferManager(const SufferManager&);

		void Input();
		void Update();
		void Draw();

		// DisplayLists Stuff
		void Audio();
		void PrepareAudio();

		u32 GetNumberOfVertexBuffers();
		u32 GetNumberOfIndexBuffers();

		void SumVertexBufferCount();
		void SumIndexBufferCount();

		u32 IsBufferCreated(const VertexBuffer* vertex_buffer);
		u32 IsBufferCreated(const IndexBuffer* index_buffer);
		u32 IsMaterialCreated(const Material* material);

		u32 NumberElements(const IndexBuffer* index_buffer);
    void SetMousePosition();


		// Threads
		ref_ptr<Thread> logic_;
		ref_ptr<Thread> input_;
		ref_ptr<Thread> audio_;

    mathmorra::Vector2 mouse_position_;

		struct Data;
		Data* data_;
	};

}

// --------------------------------------------------------------//


#endif // __SUFFER_MANAGER_H__

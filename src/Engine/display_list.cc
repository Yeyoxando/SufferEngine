/*
* Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
* Date: 11-02-2019
* DisplayLists Source
*/

#include <display_list.h>

// --------------------------------------------------------------//

Suffer::DisplayList::DisplayList(){

	dl_type_ = kDisplayListType_Invalid;
  frame_buffer_id_ = -1;

}

// --------------------------------------------------------------//

void Suffer::DisplayList::Reset() {

	Clear();
	dl_type_ = kDisplayListType_Invalid;

}

// --------------------------------------------------------------//

void Suffer::DisplayList::Clear(){

	if (dl_commands_.empty()) return;

	dl_commands_.clear();

}

// --------------------------------------------------------------//

u32 Suffer::DisplayList::Size(){

	return dl_commands_.size();

}


// --------------------------------------------------------------//

void Suffer::DisplayList::SetFrameBuffer(ResourceManager::FrameBuffer* frame_buffer){

  assert(frame_buffer != nullptr);
  if (frame_buffer == nullptr) {
    printf("NULL FrameBuffer.\n");
    return;
  }

  frame_buffer_id_ = frame_buffer->id_;

}

// --------------------------------------------------------------//

void Suffer::DisplayList::SetDisplayListType(DisplayListType dl_type) {

	if (dl_commands_.empty()){
		dl_type_ = dl_type;
	}
	else {
#ifdef DEBUG
		printf("\nError trying to change DL type without being empty: [%s]\n", __FUNCTION__);
#endif
		return;
	}

}

// --------------------------------------------------------------//

Suffer::DisplayList::DisplayListType Suffer::DisplayList::GetDisplayListType(){

	return dl_type_;

}

// --------------------------------------------------------------//

void Suffer::DisplayList::AddCommand(const ref_ptr<Command> cmd){
	
  assert(cmd.get() != nullptr && "Command is null");

	if (dl_type_ == kDisplayListType_Invalid) {
		switch (cmd->GetCommandType()) {
		case Command::CommandType::kCommandType_Render:
			dl_type_ = kDisplayListType_Render;
			break;
		case Command::CommandType::kCommandType_Audio:
			dl_type_ = kDisplayListType_Audio;
			break;
		default:
			break;
		}
	}
	else {
		switch (dl_type_){
		case Suffer::DisplayList::kDisplayListType_Render:
			if (cmd->GetCommandType() != Command::kCommandType_Render){
#ifdef DEBUG
				printf("\nError trying to adding Render command to not Render DL: [%s]\n", __FUNCTION__);
#endif
				return;
			}
			break;
		case Suffer::DisplayList::kDisplayListType_Audio:
			if (cmd->GetCommandType() != Command::kCommandType_Audio) {
#ifdef DEBUG
				printf("\nError trying to adding Audio command to not Audio DL: [%s]\n", __FUNCTION__);
#endif
				return;
			}
			break;
		default:
			break;
		}
	}

	dl_commands_.push_back(cmd);

}

// --------------------------------------------------------------//

Suffer::DisplayList & Suffer::DisplayList::operator=(DisplayList && d){

	// swap pointers to pass values without creating a copy
	std::swap(dl_commands_, d.dl_commands_);
	dl_type_ = d.dl_type_;
	d.dl_type_ = kDisplayListType_Invalid;
  frame_buffer_id_ = d.frame_buffer_id_;

	return *this;

}

// --------------------------------------------------------------//

Suffer::DisplayList::~DisplayList(){


}

// --------------------------------------------------------------//
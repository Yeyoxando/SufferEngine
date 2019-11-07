/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 11-02-2019
* DisplayLists Source
* Base structure extracted from px_render.h (Pplux)
*/

#include <display_list.h>

// --------------------------------------------------------------//

Suffer::DisplayList::DisplayList(){

	dl_type_ = kDisplayListType_NONE;

}

// --------------------------------------------------------------//

void Suffer::DisplayList::reset() {
	clear();
	dl_type_ = kDisplayListType_NONE;
}

// --------------------------------------------------------------//

void Suffer::DisplayList::clear(){
	if (dl_commands_.empty()) return;

	dl_commands_.clear();
}

// --------------------------------------------------------------//

u32 Suffer::DisplayList::size(){
	return dl_commands_.size();
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

void Suffer::DisplayList::addCommand(const ref_ptr<Command> cmd){
	if (!cmd) return;

	if (dl_type_ = kDisplayListType_NONE) {
		switch (cmd->GetCommandType()) {
		case Command::CommandType::kRender:
			dl_type_ = kDisplayListType_Render;
			break;
		case Command::CommandType::kAudio:
			dl_type_ = kDisplayListType_Audio;
			break;
		default:
			break;
		}
	}
	else {
		switch (dl_type_){
		case Suffer::DisplayList::kDisplayListType_Render:
			if (cmd->GetCommandType() != Command::kRender){
#ifdef DEBUG
				printf("\nError trying to adding Render command to not Render DL: [%s]\n", __FUNCTION__);
#endif
				return;
			}
			break;
		case Suffer::DisplayList::kDisplayListType_Audio:
			if (cmd->GetCommandType() != Command::kAudio) {
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

DisplayList & Suffer::DisplayList::operator=(DisplayList && d){
	// swap pointers to pass values without creating a real copy
	std::swap(dl_commands_, d.dl_commands_);
	dl_type_ = d.dl_type_;
	d.dl_type_ = kDisplayListType_NONE;

	return *this;
}

// --------------------------------------------------------------//

Suffer::DisplayList::~DisplayList(){


}

// --------------------------------------------------------------//
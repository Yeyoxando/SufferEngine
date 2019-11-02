/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 11-02-2019
* DisplayLists Source
* Base structure extracted from px_render.h (Pplux)
*/

#include <display_list.h>
#include <vector>

// --------------------------------------------------------------//

struct Suffer::DisplayList::Data{

	//std::vector<DisplayList::Command> commands_;

	void Reset();
	void Copy(const Data& d);

};

// --------------------------------------------------------------//

void Suffer::DisplayList::Data::Reset(){

	// Clear the std::vector of commands.
	//commands_.clear();

}

// --------------------------------------------------------------//

void Suffer::DisplayList::Data::Copy(const Data& d){

	//commands_ = d.commands_;

}

// --------------------------------------------------------------//

Suffer::DisplayList::DisplayList(){

	data_ = new Data();

}

// --------------------------------------------------------------//

Suffer::DisplayList::AudioCommands& Suffer::DisplayList::audioCommand(){
	return AudioCommands();
}

// --------------------------------------------------------------//

Suffer::DisplayList::ClearCommands& Suffer::DisplayList::clearCommand(){
	return ClearCommands();
}

// --------------------------------------------------------------//

Suffer::DisplayList Suffer::DisplayList::clone() const{

	// TODO: We have to research about that... By JBG
	DisplayList copy;
	memcpy(copy.data_, data_, sizeof(copy.data_));
	return copy;

}

// --------------------------------------------------------------//

bool Suffer::DisplayList::clone(DisplayList& out){

	if (out.data_ == nullptr) return false;
	memcpy(out.data_, this->data_, sizeof(data_));
	if (out.data_ == nullptr) return false;

}

// --------------------------------------------------------------//

Suffer::DisplayList::DisplayList(DisplayList&& d){

	data_ = d.data_;
	d.data_ = nullptr;

}

// --------------------------------------------------------------//

Suffer::DisplayList::~DisplayList(){

	if (data_ != nullptr) delete data_;
	data_ = nullptr;

}

// --------------------------------------------------------------//

void Suffer::DisplayList::AudioCommands::Play(Audio3D* source){

#ifdef ASSERT
	assert(source && "NULL AudioSource");
#endif

	if (source == nullptr) return;
	source->Play3D();

}

// --------------------------------------------------------------//

void Suffer::DisplayList::AudioCommands::Load(Audio3D* source, char* file){

#ifdef ASSERT
	assert(source && "NULL AudioSource");
#endif

	if (file == nullptr) return;
	if (source == nullptr) return;
	source->Load(file);

}

// --------------------------------------------------------------//

void Suffer::DisplayList::AudioCommands::SetGain(Audio3D* source, const float newGain) {
	
#ifdef ASSERT
	assert(source && "NULL AudioSource");
#endif

	if (source == nullptr) return;
	source->SetGain(newGain);

}

// --------------------------------------------------------------//
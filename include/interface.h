/*
 * Author: Pablo Bano Benito <banyobe@esat-alumni.com>
 * Date: 10-12-2019
 * Interface Header
 */

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

class Interface {

public:
	Interface();
	~Interface();

	// Deleted functions
	Interface(const Interface&) = delete;
	Interface& operator=(const Interface&) = delete;

	// Attributes

	// Methods
	void Init();
	void Update();
	void End();

private:
	void DrawMenuBar();
	void DockSpace(bool* p_open);
	
	// Engine Interface Structure
	void Hierarchy();
	void Console();
	void Inspector();
	void Project();

};

#endif // __INTERFACE_H__

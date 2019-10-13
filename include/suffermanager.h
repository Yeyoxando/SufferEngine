// Pablo Bano Benito <banyobe@esat-alumni.com>

#ifndef __SUFFER_MANAGER_H__
#define __SUFFER_MANAGER_H__



class SufferManager {

public:
	static SufferManager& instance();

protected:

	SufferManager();
	virtual ~SufferManager();

private:
	SufferManager(const SufferManager&);

};


#endif // __SUFFER_MANAGER_H__

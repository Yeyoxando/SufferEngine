#include <soloud.h>
#include <soloud_monotone.h>
#include <soloud_wav.h>

struct Suffer::Audio3D::Data {

  // TODO: Make a structure with these attributes.
  SoLoud::Soloud sound_;
  SoLoud::Wav wave_;
  SoLoud::handle handle_;
  SoLoud::Monotone wave_form_;

};
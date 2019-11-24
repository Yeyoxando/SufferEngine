
#include <common_definitions.h>
#if !defined _MAIN_PABLO_ && defined _MAIN_DIEGO_

#include <suffermanager.h>
#include "ref_ptr.h"
#include "scene.h"
#include "geometry.h"
#include "material.h"
#include "game_object.h"
#include "resource_manager.h"

// --------------------------------------------------------------//

int main(int argc, char* argv[]) {

  suffer.Init();


  Suffer::ref_ptr<Suffer::Scene> scene;
  scene.alloc();

  Suffer::ref_ptr<Suffer::Geometry> geometry;
  geometry.alloc();

  Suffer::ref_ptr<Suffer::ResourceManager::Texture> albedo_texture;
  albedo_texture.alloc();
  albedo_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Nearest, Suffer::ResourceManager::Texture::kTextureFilter_Nearest);
  albedo_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
  albedo_texture->LoadTextureData("../../../resources/images/box.jpg");

  Suffer::ref_ptr<Suffer::MaterialInstance> material;
  material.alloc();
  material->SetMaterialParamsType(Suffer::MaterialInstance::kParams_Default);
  material->SetColor(mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
  material->SetAlbedoTexture(albedo_texture);

  Suffer::ref_ptr<Suffer::GameObject> go_cube;
  go_cube.alloc();
  go_cube->StartUpLUA("../../../src/lua/lua_code_cube.txt");
  go_cube->SetGeometry(geometry);
  go_cube->GetGeometry()->SetDrawMode(Suffer::Geometry::kDrawMode_Triangles);
  go_cube->SetMaterial(material);
  go_cube->SetName("Cube");

  go_cube->Translate(mathmorra::Vector3(-1.0f, 0.0f, 0.0f));
  go_cube->GetGeometry()->CreateGeometryWithShape(Suffer::Geometry::kBasicShapes_Cube);



  Suffer::ref_ptr<Suffer::Geometry> geometry2;
  geometry2.alloc();

  Suffer::ref_ptr<Suffer::ResourceManager::Texture> albedo_texture2;
  albedo_texture2.alloc();
  albedo_texture2->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
  albedo_texture2->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
  albedo_texture2->LoadTextureData("../../../resources/images/earth.jpg");

  Suffer::ref_ptr<Suffer::MaterialInstance> material2;
  material2.alloc();
  material2->SetMaterialParamsType(Suffer::MaterialInstance::kParams_Default);
  material2->SetMaterialParamsType(Suffer::MaterialInstance::kParams_Default);
  material2->SetColor(mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
  material2->SetAlbedoTexture(albedo_texture2);

  Suffer::ref_ptr<Suffer::GameObject> go_sphere;
  go_sphere.alloc();
  go_sphere->StartUpLUA("../../../src/lua/lua_code_sphere.txt");
  go_sphere->SetGeometry(geometry2);
  go_sphere->GetGeometry()->SetDrawMode(Suffer::Geometry::kDrawMode_Triangles);

  go_sphere->SetMaterial(material2);
  go_sphere->Translate(mathmorra::Vector3(1.0f, 0.0f, 0.0f));
  go_sphere->SetName("Sphere");
  go_sphere->GetGeometry()->CreateGeometryWithShape(Suffer::Geometry::kBasicShapes_Sphere);





  scene->AddGameObject(go_sphere);
  scene->AddGameObject(go_cube);


  suffer.SetScene(scene);


  suffer.Run();

  suffer.Finish();

  return 0;

}

// --------------------------------------------------------------//

#endif
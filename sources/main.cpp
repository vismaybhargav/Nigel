#include "engine/Body.h"
#include "engine/World.h"
#include "raylib.h"
#include "raymath.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Nigel"

int main(void) {
    const Vector2 screen_center = Vector2Scale({SCREEN_WIDTH, SCREEN_HEIGHT}, 0.5f);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.f, 10.f, 10.f };
    camera.target = (Vector3){ 0.f, 0.f, 0.f};
    camera.up = (Vector3){ 0.f, 1.f, 0.f };
    camera.fovy = 45.f;
    camera.projection = CAMERA_PERSPECTIVE;

    Engine::Body body {
        10.f,
        Vector3Zero(),
        Vector3Zero(),
        Vector3Zero(),
        Vector3Zero()
    };

    body.add_gravity();

    Engine::World world;

    world.add_body(&body);

    Mesh mesh = GenMeshPlane(10.f, 10.f, 3, 3);
    Model model = LoadModelFromMesh(mesh);

    Texture2D texture = LoadTexture("assets/small.jpg");
    SetTextureWrap(texture, TEXTURE_WRAP_REPEAT);
    Shader tiling_shader = LoadShader(0, "assets/tiling.fs");
    float tiling[2] = { 5.f, 5.f };
    int tiling_loc = GetShaderLocation(tiling_shader, "tiling");
    SetShaderValue(tiling_shader, tiling_loc, tiling, SHADER_UNIFORM_VEC2);
    
    //model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    model.materials[0].shader = tiling_shader;
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    while (!WindowShouldClose()) {
        world.step(GetFrameTime());
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
            //DrawPlane(Vector3Zero(), (Vector2){ 10.f, 10.f }, GRAY);
            DrawModel(model, Vector3Zero(), 1.f, WHITE);
            DrawCube(body.motion_properties.position, 2.f, 2.f, 2.f, RED);
            DrawGrid(10, 1.f);
            EndMode3D();
        EndDrawing();
    }

    UnloadTexture(texture);
    UnloadModel(model);
    UnloadMesh(mesh);
    UnloadShader(tiling_shader);
    CloseWindow();

    return 0;
}

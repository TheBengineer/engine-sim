#ifndef ATG_ENGINE_SIM_ENGINE_SIM_APPLICATION_H
#define ATG_ENGINE_SIM_ENGINE_SIM_APPLICATION_H

#include "geometry_generator.h"
#include "engine_simulator.h"
#include "engine.h"
#include "simulation_object.h"
#include "ui_manager.h"
#include "dynamometer.h"
#include "oscilloscope.h"

#include "delta.h"
#include "dtv.h"

#include <vector>

class EngineSimApplication {
    public:
        EngineSimApplication();
        virtual ~EngineSimApplication();

        void initialize(void *instance, ysContextObject::DeviceAPI api);
        void run();
        void destroy();

        void setCameraPosition(const ysVector &position) { m_cameraPosition = position; }
        void setCameraTarget(const ysVector &target) { m_cameraTarget = target; }
        void setCameraUp(const ysVector &up) { m_cameraUp = up; }

        void drawGenerated(const GeometryGenerator::GeometryIndices &indices, int layer = 0);
        GeometryGenerator *getGeometryGenerator() { return &m_geometryGenerator; }

        dbasic::DefaultShaders *getShaders() { return &m_shaders; }
        dbasic::TextRenderer *getTextRenderer() { return &m_textRenderer; }

        void createObjects(Engine *engine, EngineSimulator *simulator);
        dbasic::DeltaEngine *getEngine() { return &m_engine; }

        float pixelsToUnits(float pixels) const;
        float unitsToPixels(float units) const;

        ysVector getBackgroundColor() const { return m_background; }
        ysVector getHightlight1Color() const { return m_highlight1; }
        ysVector getWhite() const { return ysMath::Constants::One; }
        ysVector getPink() const { return m_pink; }
        ysVector getGreen() const { return m_green; }
        ysVector getYellow() const { return m_yellow; }
        ysVector getRed() const { return m_red; }
        ysVector getOrange() const { return m_orange; }
        ysVector getBlue() const { return m_blue; }

        dbasic::AssetManager *getAssetManager() { return &m_assetManager; }

    protected:
        void renderScene();

    protected:
        virtual void initialize();
        virtual void process(float dt);
        virtual void render();

        float m_displayHeight;

        dbasic::ShaderSet m_shaderSet;
        dbasic::DefaultShaders m_shaders;

        dbasic::DeltaEngine m_engine;
        dbasic::AssetManager m_assetManager;

        ysVector m_cameraPosition;
        ysVector m_cameraTarget;
        ysVector m_cameraUp;

        std::string m_assetPath;

        ysGPUBuffer *m_geometryVertexBuffer;
        ysGPUBuffer *m_geometryIndexBuffer;

        GeometryGenerator m_geometryGenerator;
        dbasic::TextRenderer m_textRenderer;

        std::vector<SimulationObject *> m_objects;
        Engine m_iceEngine;
        EngineSimulator m_simulator;
        Dynamometer m_dyno;
        double m_dynoSpeed;
        double m_torque;

        UiManager m_uiManager;
        Oscilloscope *m_oscilloscope;

        bool m_paused;

    protected:
        void startRecording();
        void updateScreenSizeStability();
        bool readyToRecord();
        void stopRecording();
        void recordFrame();
        bool isRecording() const { return m_recording; }

        static constexpr int ScreenResolutionHistoryLength = 5;
        int m_screenResolution[ScreenResolutionHistoryLength][2];
        int m_screenResolutionIndex;
        bool m_recording;

        ysVector m_background;
        ysVector m_foreground;
        ysVector m_shadow;
        ysVector m_highlight1;
        ysVector m_highlight2;

        ysVector m_pink;
        ysVector m_orange;
        ysVector m_yellow;
        ysVector m_red;
        ysVector m_green;
        ysVector m_blue;

        ysAudioBuffer *m_audioBuffer;
        ysAudioSource *m_audioSource;

#ifdef ATG_ENGINE_SIM_VIDEO_CAPTURE
        atg_dtv::Encoder m_encoder;
#endif /* ATG_ENGINE_SIM_VIDEO_CAPTURE */
};

#endif /* ATG_ENGINE_SIM_ENGINE_SIM_APPLICATION_H */

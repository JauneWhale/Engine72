#pragma once

//**************************************************************
// 这个文件下面都是各种章节的测试App
//**************************************************************

#include "../Core/GameLoopApp.h"
#include "../Core/D3D12/D3D12Renderer.h"
#include "../Core/UploadBuffer.h"
#include "../Core/FrameResource.h"
#include "../Core/Mesh/Waves.h"

// Lightweight structure stores parameters to draw a shape.  This will
// vary from app-to-app.
struct RenderItem
{
    RenderItem() = default;

    // World matrix of the shape that describes the object's local space
    // relative to the world space, which defines the position, orientation,
    // and scale of the object in the world.
    XMFLOAT4X4 World = MathHelper::Identity4x4();

    // Dirty flag indicating the object data has changed and we need to update the constant buffer.
    // Because we have an object cbuffer for each FrameResource, we have to apply the
    // update to each FrameResource.  Thus, when we modify obect data we should set 
    // NumFramesDirty = gNumFrameResources so that each frame resource gets the update.
    int NumFramesDirty = gNumFrameResources;

    // Index into GPU constant buffer corresponding to the ObjectCB for this render item.
    UINT ObjCBIndex = -1;

    MeshGeometry* Geo = nullptr;

    // Primitive topology.
    D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    // DrawIndexedInstanced parameters.
    UINT IndexCount = 0;
    UINT StartIndexLocation = 0;
    int BaseVertexLocation = 0;
};

//**************************************************************
// Chapter 4: 初始化一个最小Renderer
//**************************************************************
namespace InitDirect3DApp
{
    class InitDirect3DMinimalRenderer : public D3D12Renderer
    {
    public:
        InitDirect3DMinimalRenderer() = default;
        ~InitDirect3DMinimalRenderer() = default;

        virtual void Render(const GameTimer& gt, const CameraBase* camera) override;
    };

    class InitDirect3DApp : public GameLoopApp
    {
    public:
        InitDirect3DApp(HINSTANCE hInstance)
            : GameLoopApp(hInstance, new InitDirect3DMinimalRenderer()) {}
        InitDirect3DApp(const InitDirect3DApp& rhs) = delete;
        InitDirect3DApp& operator=(const InitDirect3DApp& rhs) = delete;
        ~InitDirect3DApp() = default;
    };
}

//**************************************************************
// Chapter 6: 绘制一个Box，都是临时的数据结构
//**************************************************************
using namespace DirectX;
using namespace DirectX::PackedVector;

namespace BoxApp
{
    struct ObjectConstants
    {
        XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
    };

    class BoxApp : public GameLoopApp
    {
    public:
        BoxApp(HINSTANCE hInstance);
        BoxApp(const BoxApp& rhs) = delete;
        BoxApp& operator=(const BoxApp& rhs) = delete;
        ~BoxApp() = default;

    private:
        virtual void LogicUpdate(const GameTimer& gt) override;
        virtual void OnResize() override;

        DragMouseRotateInput* inputData = nullptr;
        RotatScaleCamera* mRSCamera;
    };

    class Box3DMinimalRenderer : public D3D12Renderer
    {
    public:
        virtual void Render(const GameTimer& gt, const CameraBase* camera)override;
        virtual bool InitializeRenderer(int clientWidth, int clientHeight, HWND targetWnd) override;
    private:
        // Self Functions
        void BuildDescriptorHeaps();
        void BuildConstantBuffers();
        void BuildRootSignature();
        void BuildShadersAndInputLayout();
        void BuildBoxGeometry();
        void BuildPSO();

    private:

        ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
        ComPtr<ID3D12DescriptorHeap> mCbvHeap = nullptr;

        std::unique_ptr<UploadBuffer<ObjectConstants>> mObjectCB = nullptr;

        std::unique_ptr<MeshGeometry> mBoxGeo = nullptr;

        ComPtr<ID3DBlob> mvsByteCode = nullptr;
        ComPtr<ID3DBlob> mpsByteCode = nullptr;

        std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

        ComPtr<ID3D12PipelineState> mPSO = nullptr;
    };
}

//**************************************************************
// Chapter 6: 绘制各种shape，都是临时的数据结构
//**************************************************************
namespace ShapeApp
{
    class ShapeApp : public GameLoopApp
    {
    public:
        ShapeApp(HINSTANCE hInstance);
        ShapeApp(const ShapeApp& rhs) = delete;
        ShapeApp& operator=(const ShapeApp& rhs) = delete;
        ~ShapeApp() = default;

    private:
        virtual void LogicUpdate(const GameTimer& gt) override;
        virtual void OnResize() override;

        DragMouseRotateInput* inputData = nullptr;
        RotatScaleCamera* mRSCamera;
    };

    class ShapeAppRenderer : public D3D12Renderer
    {
    public:
        virtual void Render(const GameTimer& gt, const CameraBase* camera)override;
        virtual bool InitializeRenderer(int clientWidth, int clientHeight, HWND targetWnd) override;
        void AdditionalUpdate(const GameTimer& gt, const CameraBase* camera, int clientWidth, int clientHeight);
    private:
        // Self Functions
        void BuildDescriptorHeaps();
        void BuildConstantBufferViews();
        void BuildRootSignature();
        void BuildShadersAndInputLayout();
        void BuildShapeGeometry();
        void BuildPSOs();
        void BuildFrameResources();
        void BuildRenderItems();
        void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);

        void OnKeyboardInput(const GameTimer& gt);
        void UpdateObjectCBs(const GameTimer& gt);
        void UpdateMainPassCB(const GameTimer& gt, const CameraBase* camera, int clientWidth, int clientHeight);

    private:

        ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
        ComPtr<ID3D12DescriptorHeap> mCbvHeap = nullptr;

        std::unique_ptr<UploadBuffer<ObjectConstants>> mObjectCB = nullptr;

        ComPtr<ID3DBlob> mvsByteCode = nullptr;
        ComPtr<ID3DBlob> mpsByteCode = nullptr;
        std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
        std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> mPSOs;
        // List of all the render items.
        std::vector<std::unique_ptr<RenderItem>> mAllRitems;
        // Render items divided by PSO.
        std::vector<RenderItem*> mOpaqueRitems;

        std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

        ComPtr<ID3D12PipelineState> mPSO = nullptr;
        std::vector<std::unique_ptr<FrameResource>> mFrameResources;
        FrameResource* mCurrFrameResource = nullptr;
        int mCurrFrameResourceIndex = 0;

        bool mIsWireframe = false;

        PassConstants mMainPassCB;

        UINT mPassCbvOffset = 0;
    };
}


//**************************************************************
// Chapter 6: 绘制一个地形，都是临时的数据结构
//**************************************************************
//namespace LandAndWavesApp
//{
//
//    enum class RenderLayer : int
//    {
//        Opaque = 0,
//        Count
//    };
//
//    class LandAndWavesApp : public GameLoopApp
//    {
//    public:
//        LandAndWavesApp(HINSTANCE hInstance);
//        LandAndWavesApp(const LandAndWavesApp& rhs) = delete;
//        LandAndWavesApp& operator=(const LandAndWavesApp& rhs) = delete;
//        ~LandAndWavesApp() = default;
//
//    private:
//        virtual void LogicUpdate(const GameTimer& gt) override;
//        virtual void OnResize() override;
//
//    private:
//
//        void OnKeyboardInput(const GameTimer& gt);
//        void UpdateCamera(const GameTimer& gt);
//    };
//
//    class LandAndWavesRenderer : public D3D12Renderer
//    {
//    public:
//        virtual void Render(const GameTimer& gt, const CameraBase* camera)override;
//        virtual bool InitializeRenderer(int clientWidth, int clientHeight, HWND targetWnd) override;
//    private:
//        void UpdateObjectCBs(const GameTimer& gt);
//        void UpdateMainPassCB(const GameTimer& gt);
//        void UpdateWaves(const GameTimer& gt);
//
//        void BuildRootSignature();
//        void BuildShadersAndInputLayout();
//        void BuildLandGeometry();
//        void BuildWavesGeometryBuffers();
//        void BuildPSOs();
//        void BuildFrameResources();
//        void BuildRenderItems();
//        void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);
//
//        float GetHillsHeight(float x, float z)const;
//        XMFLOAT3 GetHillsNormal(float x, float z)const;
//
//    private:
//
//        std::vector<std::unique_ptr<FrameResource>> mFrameResources;
//        FrameResource* mCurrFrameResource = nullptr;
//        int mCurrFrameResourceIndex = 0;
//
//        UINT mCbvSrvDescriptorSize = 0;
//
//        ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
//
//        std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
//        std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;
//        std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> mPSOs;
//
//        std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;
//
//        RenderItem* mWavesRitem = nullptr;
//
//        // List of all the render items.
//        std::vector<std::unique_ptr<RenderItem>> mAllRitems;
//
//        // Render items divided by PSO.
//        std::vector<RenderItem*> mRitemLayer[(int)RenderLayer::Count];
//
//        std::unique_ptr<Waves> mWaves;
//
//        PassConstants mMainPassCB;
//
//        bool mIsWireframe = false;
//
//        XMFLOAT3 mEyePos = { 0.0f, 0.0f, 0.0f };
//        XMFLOAT4X4 mView = MathHelper::Identity4x4();
//        XMFLOAT4X4 mProj = MathHelper::Identity4x4();
//
//        float mSunTheta = 1.25f * XM_PI;
//        float mSunPhi = XM_PIDIV4;
//
//        POINT mLastMousePos;
//
//        DragMouseRotateCommand* mRotateData = nullptr;
//    };
//}
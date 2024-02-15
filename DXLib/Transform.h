#pragma once


namespace DX {
	class DXLIB_DLL Transform
	{
	public:
		Transform();

		DirectX::XMMATRIX WorldMatrix()const;
		DirectX::XMMATRIX S()const;
		DirectX::XMMATRIX R()const;
		DirectX::XMMATRIX T()const;

		DirectX::XMFLOAT3 GetPos()const { return pos; }
		DirectX::XMFLOAT3 GetForward()const {
			return forward;
		}
		DirectX::XMFLOAT3 GetUp()const
		{
			return up;
		}
		DirectX::XMFLOAT3 GetRight()const
		{
			return right;
		}
		DirectX::XMFLOAT3 GetScale()const
		{
			return scale;
		}
		void SetTranslation(float x, float y, float z) {
			pos = { x,y,z };
		}
		void SetTranslation(DirectX::XMFLOAT3 newPos) {
			pos = newPos;
		}
		void SetRot(DirectX::XMFLOAT3 _forward);
		void SetRot(DirectX::XMFLOAT3 _forward, DirectX::XMFLOAT3 _up);
		void SetRot(DirectX::XMFLOAT3 _forward, DirectX::XMFLOAT3 _up, DirectX::XMFLOAT3 _right);
		void Rotate(DirectX::XMFLOAT3 axis, float rad);
		void SetScale(float x) {
			scale = { x,x,x };
		}
		void SetScale(float x, float y, float z) {
			scale = { x,y,z };
		}
		void SetScale(DirectX::XMFLOAT3 newScale) {
			scale = newScale;
		}

	private:

		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 forward;
		DirectX::XMFLOAT3 right;
		DirectX::XMFLOAT3 up;
		DirectX::XMFLOAT3 scale;
	};
}


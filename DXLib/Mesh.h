#pragma once

#include "Component.h"
#include "Vertex.h"

namespace DX {
	
	class Object;

	enum VertexElementType
	{
		VE_Position2D,
		VE_Position3D,
		VE_Texture2D,
		VE_Normal,
		VE_Float3Color,
		VE_Float4Color,
		VE_BGRAColor,
		VE_Max
	};

	class DXLIB_DLL VertexLayout
	{
	public:


		template<VertexElementType> struct Map;
		template<> struct Map<VE_Position2D>
		{
			using SysType = DirectX::XMFLOAT2;
			static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32_FLOAT;
			static constexpr const char* semantic = "POSITION";
		};
		template<> struct Map<VE_Position3D>
		{
			using SysType = DirectX::XMFLOAT3;
			static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32B32_FLOAT;
			static constexpr const char* semantic = "POSITION";
		};
		template<> struct Map<VE_Texture2D>
		{
			using SysType = DirectX::XMFLOAT2;
			static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32_FLOAT;
			static constexpr const char* semantic = "TEXCOORD";
		};
		template<> struct Map<VE_Normal>
		{
			using SysType = DirectX::XMFLOAT3;
			static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32B32_FLOAT;
			static constexpr const char* semantic = "NORMAL";
		};
		template<> struct Map<VE_Float3Color>
		{
			using SysType = DirectX::XMFLOAT3;
			static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32B32_FLOAT;
			static constexpr const char* semantic = "COLOR";
		};
		template<> struct Map<VE_Float4Color>
		{
			using SysType = DirectX::XMFLOAT4;
			static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
			static constexpr const char* semantic = "COLOR";
		};
		template<> struct Map<VE_BGRAColor>
		{
			using SysType = DirectX::XMUINT4;
			static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_G8R8_G8B8_UNORM;
			static constexpr const char* semantic = "COLOR";
		};

		class DXLIB_DLL Element
		{
		public:
			Element(VertexElementType type, int offset);

			int GetOffsetAfter()const;
			int GetOffset()const;
			int Size() const;

			static int SizeOf(VertexElementType type);

			VertexElementType GetType() const;

			D3D11_INPUT_ELEMENT_DESC GetDesc() const;


		private:

			template<VertexElementType Type>
			static constexpr D3D11_INPUT_ELEMENT_DESC GenerateDesc(int offset)
			{
				return { Map<Type>::semantic, 0, Map<Type>::dxgiFormat, 0, (UINT)offset, D3D11_INPUT_PER_VERTEX_DATA, 0 };
			}

			VertexElementType m_type;
			int m_offset;
		};

		int Count()const;
		void Clear();

		template<VertexElementType Type>
		const Element* Resolve() const
		{
			for (const auto& e : m_elements)
			{
				if (e.GetType() == Type)
					return &e;
			}

			return nullptr;
		}
		const Element* ResolveByIndex(unsigned int i)const;
		VertexLayout& Append(VertexElementType type);
		int Size() const;
		std::vector<D3D11_INPUT_ELEMENT_DESC> GetLayout() const;

	private:
		std::vector<Element> m_elements;
	};

	class DXLIB_DLL Vertex
	{
		friend class Mesh;

	public:
		template<VertexElementType Type>
		auto& Attr()
		{
			const auto* element = m_layout.Resolve<Type>();
			auto* attribute = m_data + element->GetOffset();
			return *reinterpret_cast<VertexLayout::Map<Type>::SysType*>(attribute);
		}

		template<typename T>
		void SetAttributeByIndex(unsigned int i, T&& val)
		{
			const auto* element = m_layout.ResolveByIndex(i);
			auto* attribute = m_data + element->GetOffset();
			switch (element->GetType())
			{
			case VertexLayout::VE_Position2D:
				SetAttributeByIndex<VE_Position2D>(attribute, std::forward<T>(val));
				break;
			case VertexLayout::VE_Texture2D:
				SetAttributeByIndex<VE_Texture2D>(attribute, std::forward<T>(val));
				break;
			case VertexLayout::VE_Position3D:
				SetAttributeByIndex<VE_Position3D>(attribute, std::forward<T>(val));
				break;
			case VertexLayout::VE_Normal:
				SetAttributeByIndex<VE_Normal>(attribute, std::forward<T>(val));
				break;
			case VertexLayout::VE_Float3Color:
				SetAttributeByIndex<VE_Float3Color>(attribute, std::forward<T>(val));
				break;
			case VertexLayout::VE_Float4Color:
				SetAttributeByIndex<VE_Float4Color>(attribute, std::forward<T>(val));
				break;
			case VertexLayout::VE_BGRAColor:
				SetAttributeByIndex<VE_BGRAColor>(attribute, std::forward<T>(val));
				break;
			}
		}

	protected:

		Vertex(char* data, const VertexLayout& layout);

	private:
		template<typename First, typename ...Rest>
		void SetAttributeByIndex(unsigned int i, First&& first, Rest&&... rest)
		{
			SetAttributeByIndex(i, std::forward<First>(first));
			SetAttributeByIndex(i + 1, std::forward<Rest>(rest)...);
		}
		template<VertexElementType DestType, typename SrcType>
		void SetAttributeByIndex(char* data, SrcType&& val)
		{
			using Dest = typename VertexLayout::Map<DestType>::SysType;
			if constexpr (std::is_assignable<Dest, SrcType>::value)
			{
				*reinterpret_cast<Dest*>(data) = val;
			}
		}

		VertexLayout m_layout;
		char* m_data = nullptr;
	};

	class DXLIB_DLL Mesh : public Component
	{
	public:
		Mesh();
		~Mesh();

		void GetLBound(OUT DirectX::XMFLOAT3* minPt, OUT DirectX::XMFLOAT3* maxPt);
		D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveType() { return m_primitiveType; }

		void SetIndice(const int* indice, int indexCount);

		void Update(ID3D11Device* device);


		void Apply(ID3D11DeviceContext* dContext)const override;

	protected:

		void SetPrimitiveType(D3D11_PRIMITIVE_TOPOLOGY p) { m_primitiveType = p; }

		DirectX::XMFLOAT3 m_lMinPt, m_lMaxPt;
		ID3D11Buffer* m_vertexBuffer = nullptr;
		ID3D11Buffer* m_indexBuffer = nullptr;
		D3D11_PRIMITIVE_TOPOLOGY m_primitiveType;


		int* m_indice;
		int m_indexCount;

		bool isNeedUpdate;

	public:
		const VertexLayout& GetLayout() const;
		const char* GetData() const;
		int SizeByte() const;
		int Count() const;
		template<typename ...Params>
		void EmplaceBack(Params&&... params)
		{
			assert(sizeof...(params) == m_layout.Count() && "Param count doesn't match");

			m_buffer.resize(m_buffer.size() + m_layout.Size());
			Back().SetAttributeByIndex(0, std::forward<Params>(params)...);
		}
		void EmplaceBack(int count = 1);
		Vertex Front();
		Vertex Back();
		Vertex GetVertex(int i);
		void Clear();

	private:
		VertexLayout m_layout;
		std::vector<char> m_buffer;
	};
}

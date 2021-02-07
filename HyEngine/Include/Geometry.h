#pragma once


namespace HyEngine
{
	class Geometry
	{
	public:
		template <typename T>
		static T* CreateGeometry()
		{
			for (auto& geo : geometries)
			{
				T * result = dynamic_cast<T>(geo);
				if (result != nullptr)
					return result;
			}
			T* geometry = new T();
			geometry->CreateVertex();
			geometry->CreateIndex();
			geometries.push_back(geometry);
			return geometry;
		}

	protected:
		virtual void CreateVertex() = 0;
		virtual void CreateIndex() = 0;
	public:
		IDirect3DVertexBuffer9* GetVertexBuffer();
		int GetVertexSize();
		int GetVertexCount();
		DWORD GetFVF();
		IDirect3DIndexBuffer9* GetIndexBuffer();
		int GetPrimitiveCount();

	private:
		// vertex
		int m_vertexSize;
		int m_vertexCount;
		DWORD m_vertexFVF;
		IDirect3DVertexBuffer9 * m_pVertexBuffer = nullptr;

		// index
		int m_indexSize;
		int m_indexCount;
		int m_indexFMT;
		IDirect3DIndexBuffer9* m_pIndexBuffer = nullptr;

		int m_primitiveCount;

	private:
		static std::vector<Geometry*> geometries;
	};

}
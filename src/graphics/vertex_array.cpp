#include "vertex_array.hpp"

std::ostream& operator<<( std::ostream& out, const VertexArray& vertex_array )
{
    out <<  "vertex buffer info:\n" <<
            "id:" << vertex_array.m_id << "\n" <<
            "bound:" << (( vertex_array.m_is_bind )? "true\n" : "false\n") <<
            "attribute_count:" << vertex_array.m_attribute_count << "\n";

    for( int i = 0; i < vertex_array.m_attribute_count; ++i )
        std::cout << "location " << i <<
        ((vertex_array.m_attributes[i].location != -1)? " is bound.\n" : "is not bound.\n");
                                        

    return out;
}

VertexArray::AttributeData::AttributeData() : location(-1), vertex_buffer(nullptr) {}

VertexArray::VertexArray() : m_id(0), m_attribute_count(0), m_is_bind(false) {}

void VertexArray::Init()
{
    glGenVertexArrays(1,&m_id);
}

void VertexArray::Bind( bool bind )
{
    if( bind && !m_is_bind )
    {
        glBindVertexArray(m_id);
        m_is_bind = true;
    }

    else if( !bind && m_is_bind )
    {
        glBindVertexArray(0);
        m_is_bind = false;
    }
}

VertexArray& VertexArray::AddLayout( VertexBuffer& vertex_buffer )
{
    if( m_attribute_count > max_attributes )
    {
        CORE_LOG_WARNING("cannot add layout to vertex array.exceeding it's capacity.\n");
        return *this;
    }

    if( !vertex_buffer.IsFilled() )
    {
        CORE_LOG_WARNING("empty vertex buffer used for rendering!");
        return *this;
    }
    
    Bind();

    vertex_buffer.Bind();
/*
    std::vector<uint16_t> offsets = {0}; // the first offset is always zero.
    std::vector<GLint> component_counts;
    std::vector<GLenum> gl_types;

    auto element_count = vertex_buffer.m_layout.m_elements.size();

    for( uint32_t i = 0; i < element_count; ++i )
    {
        auto data_type = vertex_buffer.m_layout.m_elements.at(i).m_type;

        GLint component_count = CalculateComponent(data_type);
        GLenum gl_type = CalculateType(data_type);
        GLint type_size = CalculateSize(data_type);

        m_stride += type_size;

        component_counts.push_back(component_count);
        gl_types.push_back(gl_type);

        if( i < element_count - 1 ) // we have set the first offset out of loop to zero.
            offsets.push_back(m_stride); // so this code should execute 1 less time than the whole loop.
    }

    for( uint32_t i = 0; i < element_count; ++i )
    {
        glVertexAttribPointer(m_attribute_count,component_counts.at(i),gl_types.at(i),GL_FALSE,
                              m_stride,(void*)offsets.at(i));

        m_attributes[m_attribute_count].location = m_attribute_count;
        m_attributes[m_attribute_count].vertex_buffer = &vertex_buffer;
        
        glEnableVertexAttribArray(m_attribute_count++);
    }
*/

    auto stride = vertex_buffer.m_layout.m_stride;

    for( uint8_t i = 0; i < vertex_buffer.m_layout.m_elements.size(); ++i )
    {
        auto data_type = vertex_buffer.m_layout.m_elements.at(i).m_type;
        

        GLint component_count = CalculateComponent(data_type);
        GLenum gl_type = CalculateType(data_type);
        GLint type_size = CalculateSize(data_type);

        glVertexAttribPointer(m_attribute_count,component_count,gl_type, GL_FALSE,
                              stride,(void*)vertex_buffer.m_layout.m_offsets.at(i));

        glEnableVertexAttribArray(m_attribute_count++);
    }

    vertex_buffer.Bind(false);
    
    return *this;
}

VertexArray& VertexArray::RemoveLayout( GLint location )
{
    auto loc = std::find_if(std::begin(m_attributes), std::end(m_attributes), [&]( AttributeData& data )
    {
        if( data.location == location )
            return true;

        return false;
    });

    if( loc != std::end(m_attributes) )
    {
        Bind();
        
        glDisableVertexAttribArray(location);
        loc->location = -1;
        loc->vertex_buffer = nullptr;
    }

    return *this;
}

VertexArray& VertexArray::SetIndexBuffer( IndexBuffer& buffer )
{
    Bind();
    buffer.Bind();

    return *this;
}

VertexArray& VertexArray::RemoveIndexBuffer()
{
    Bind();
    m_bound_ebo->Bind(false);

    m_bound_ebo = nullptr;

    return *this;
}

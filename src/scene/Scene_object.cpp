#include "Scene_object.h"
#include <glm/gtx/string_cast.hpp>
#include<cassert>

PROKARYOTIC::unique_id Scene_object::m_Unique_ID(0,0,0, PROKARYOTIC::CLASS_SCENE_OBJECT);

Scene_object::Scene_object(Mesh<Vertex>* mesh, Material* material)
: p_mesh(mesh), p_material(material), m_ID(0)
{
    m_ID.raw = generate_ID();
}

Scene_object::~Scene_object()
{
    for (unsigned int i = 0; i < m_Children.size(); ++i)
    {
        delete m_Children[i];
    }  
}

std::uint64_t  Scene_object::generate_ID() 
{ 
    if (m_Unique_ID.MIN < 0xFFFF)
    {
        m_Unique_ID.MIN++;

        return m_Unique_ID.raw;
    }
    else
    if (m_Unique_ID.MAJ < 0xFFFF)
    {
        m_Unique_ID.MIN = 0;
        m_Unique_ID.MAJ++;

        return m_Unique_ID.raw;
    }

    assert(m_Unique_ID.MAJ < 0xFFFF);     
}

void  Scene_object::set_Position(glm::vec3 position)
{
    m_Position = position;
    m_Recalc = true;
}

void  Scene_object::set_Scale(glm::vec3 scale)
{
    m_Scale = scale;
    m_Recalc = true;
}

void  Scene_object::set_Scale(float scale)
{
    m_Scale = glm::vec3(scale);
    m_Recalc = true;
}
 
void  Scene_object::set_Rotation(float radians, glm::vec3 axis)
{
    m_Rotation = glm::vec4(axis,radians);
    m_Recalc = true;
}

glm::vec3  Scene_object::get_World_position()
{
    glm::mat4 transform = get_Transform();
    glm::vec4 pos = transform * glm::vec4(m_Position, 1.0f);

    glm::vec3 result = glm::vec3(pos.x, pos.y, pos.z);

    return result;
}

glm::vec3  Scene_object::get_World_scale()
{
    glm::mat4 transform = get_Transform();
    glm::vec3 scale = glm::vec3(transform[0][0], transform[1][1], transform[2][2]);

    if (scale.x < 0.0f) scale.x *= -1.0f;
    if (scale.y < 0.0f) scale.y *= -1.0f;
    if(scale.z < 0.0f) scale.z *= -1.0f;

    return scale;
}

void  Scene_object::add_Child(Scene_object *obj)
{ 
    // Scene objects aren't allowed to exist under multiple parents.
    if (obj->m_Parent)
        obj->m_Parent->remove_Child(obj->get_ID());

    obj->m_Parent = this;
    m_Children.push_back(obj);
}

void  Scene_object::remove_Child(std::uint64_t id)
{
    auto it = std::find(m_Children.begin(), m_Children.end(), get_Child(id));

    if(it != m_Children.end())
        m_Children.erase(it);
}

Scene_object* Scene_object::get_Child(std::uint64_t id)
{
    for (unsigned int i = 0; i < m_Children.size(); ++i)
    {
        if(m_Children[i]->get_ID() == id)
            return m_Children[i];
    }

    return nullptr;
}

Scene_object* Scene_object::get_Child_by_index(unsigned int index)
{
    assert(index < get_Child_count());

    return m_Children[index];
}

void  Scene_object::set_Transform(glm::mat4 transform)
{
    m_Transform = transform;
    m_Recalc = true;
}

glm::mat4  Scene_object::get_Transform()
{
    if (m_Recalc)
        update_Transform(false);

    return m_Transform;
}

void  Scene_object::update_Transform(bool Update_prev_transform)
{
    // if specified, store current transform as prev transform (for calculating motion vectors)
    if (Update_prev_transform)
        m_Prev_transform = m_Transform;

    // we only do this if the node itself or its parent is flagged as dirty
    if (m_Recalc)
    {
        // first translation , then scale, then rotate.
        m_Transform = glm::translate(m_Transform, m_Position);
        m_Transform = glm::scale(m_Transform, m_Scale); 
        m_Transform = glm::rotate(m_Transform, m_Rotation.w, glm::vec3(m_Rotation));

        if (m_Parent)
        {
            m_Transform = m_Parent->m_Transform * m_Transform;
        }        
    }

    for (int i = 0; i < m_Children.size(); ++i)
    {
        if (m_Recalc)
        {
            m_Children[i]->m_Recalc = true;
        }

        m_Children[i]->update_Transform(Update_prev_transform);
    }

    m_Recalc = false;
}


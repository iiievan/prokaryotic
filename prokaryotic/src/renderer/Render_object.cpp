#include "Render_object.h"

namespace PROKARYOTIC
{
	static unique_id m_Unique_ID(0, 0, 0, TYPE_NA);

    std::uint64_t  Render_object::m_generate_ID()
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
}
#include "Geometry/Vertex.h"
#include "Math/Parameter.h"

namespace Rocket {
    namespace Geometry {
        bool Vertex::IsCoincidentWith(const Vertex* v) {
            if(id == v->id)   // Check ID
                return true;
            else if((position - v->position).norm() < EPS)  // Check Position
                return true;
            else
                return false;
        }

        bool CompareVertex(const VertexPtr& lhs, const VertexPtr& rhs) {
            // assumes that the implementation uses a flat address space
            return lhs->position.squaredNorm() < rhs->position.squaredNorm(); 
        }
    }
}

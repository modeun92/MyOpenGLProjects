#include "GlmMvpShader.h"
void GlmMvpShader::SetModel(glm::mat4 a_Model) const {
    SetMat4(MODEL, a_Model);
}
void GlmMvpShader::SetView(glm::mat4 a_View) const {
    SetMat4(VIEW, a_View);
}
void GlmMvpShader::SetProjection(glm::mat4 a_Projection) const {
    SetMat4(PROJECTION, a_Projection);
}
void GlmMvpShader::SetMvp(glm::mat4 a_Model, glm::mat4 a_View, glm::mat4 a_Projection) const {
    SetModel(a_Model);
    SetView(a_View);
    SetProjection(a_Projection);
}
#include "Testing.h"
#include "imgui_internal.h"
#include <iostream>


Testing::Testing()
{
    Animation<float>* a1 = new Animation<float>;
    a1->name = "Widget 1";
    a1->addTransformNode(VEC2(1.0f, 0.0f), 1.0f);
    /*a1->addTransformNode(VEC2(2.0f, 0.0f), 2.0f);
    a1->addTransformNode(VEC2(2.0f, 2.0f), 2.2f);*/
    _animations.push_back(a1);
}


Testing::~Testing()
{
}

void Testing::Render( ) {
   
    if (show_columns)
    {
        ImGui::Begin("Columns", &show_columns);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

        
        if (ImGui::TreeNode("Tree"))
        {
            ImGui::Columns(2, "tree", false);

            for (int x = 0; x < _animations.size(); x++)
            {
                int ColorPickerID = 0;
                if (bool open1 = ImGui::TreeNode((void*)_animations[x]->name.c_str(), _animations[x]->name.c_str(), x))
                {

                    ImGui::Text("");

                    ImGui::SetColumnWidth(0, ImGui::GetFontSize() * 7);
                    ImGui::BeginGroup();
                    ImGui::Text("Position");
                    ImGui::Text("");
                    ImGui::Text("Scale");
                    ImGui::Text("");
                    ImGui::Text("Color");
                    ImGui::Text("");
                    ImGui::Text("Special");
                    ImGui::EndGroup();

                    ImGui::NextColumn();

                    ImGui::Text("");
                    ImGui::Text("");
                    ImGui::BeginGroup();

                    /* Node positioning info */
                    ImDrawList* draw_list = ImGui::GetWindowDrawList();
                    const ImVec2* p = &ImGui::GetCursorScreenPos();
                    const float     nodeSize = 5.0f;
                    ImVec2          cursorPos = *p;
                    cursorPos.y += nodeSize;
                    ImGuiWindow* win = ImGui::GetCurrentWindow();
                    const float     timeline_radius = 6.0f;// max_time / 0.5f;
                    const ImU32 inactive_color = ImGui::ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Button]);
                    const ImU32 active_color = ImGui::ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_ButtonHovered]);
                    ImGui::BeginChild("##ScrollingRegion", ImVec2(0, ImGui::GetFontSize() * 10), true, ImGuiWindowFlags_HorizontalScrollbar);
                    // Draw nodes for every animation type
                    for (auto a = 0; a < _animations[x]->transformNodes.size(); a++) {

                        /*std::string popupId = std::to_string(_animations[x]->transformNodes[a].first.x)
                            + std::to_string(_animations[x]->transformNodes[a].first.y)
                            + std::to_string(_animations[x]->transformNodes[a].second);
                        ImGui::PushID(popupId.c_str());*/

                        cursorPos.x += win->Size.x * _animations[x]->transformNodes[a].second / max_time;
                        ImGui::SetCursorScreenPos(cursorPos - ImVec2(timeline_radius, timeline_radius));

                        ImGui::InvisibleButton("##Node", ImVec2(2 * timeline_radius, 2 * timeline_radius));
                        //std::cout << "Item: "<< a <<"Is item active ? :" << (ImGui::IsItemActive() ? "true" : "false") << std::endl;
                        if (ImGui::IsItemActive() && ImGui::IsMouseDragging(0, 0.0f)){
                            _animations[x]->transformNodes[a].second += ImGui::GetIO().MouseDelta.x / win->Size.x * max_time;
                            if (_animations[x]->transformNodes[a].second < 0.0f)
                                _animations[x]->transformNodes[a].second = 0.0f;
                        }
                        if (ImGui::IsItemHovered()) {
                            ImGui::BeginTooltip();
                            Animation<float>::displayTransformPopup(_animations[x]->transformNodes[a]);
                            ImGui::EndTooltip();
                        }
                        draw_list->AddCircleFilled(cursorPos, nodeSize, ImGui::IsItemActive() || ImGui::IsItemHovered() ? active_color : inactive_color);

                        if (a != _animations[x]->transformNodes.size())
                            ImGui::SameLine();

                        //ImGui::PopID();
                    }





                    const float fwidth = ImGui::GetColumnWidth();
                    const float fheight = ImGui::GetContentRegionAvail().y;
                    for (auto lineHorizontalPos = 0.0f; lineHorizontalPos < max_time; lineHorizontalPos += 0.5f) {
                        draw_list->AddLine(ImVec2((p->x + lineHorizontalPos)/fwidth  , p->y), ImVec2((p->x + lineHorizontalPos) / fwidth, p->y + fheight), ImColor(0.0f, 0.0f, 1.0f, 0.6f));
                    }



                    ImGui::EndChild();
                    ImGui::EndGroup();










                    //ImGui::Text("Position");

                    //ImGui::NextColumn(); // Right

                    //ImGui::Text("");
                    //ImDrawList*     draw_list = ImGui::GetWindowDrawList();
                    //const ImVec2*   p = &ImGui::GetCursorScreenPos();
                    //ImVec2          cursorPos = *p;
                    //const float     nodeSize = 5.0f;
                    //ImGuiWindow*    win = ImGui::GetCurrentWindow();
                    //const float     timeline_radius = max_time / 0.5f;
                    //const ImU32 inactive_color = ImGui::ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Button]);
                    //const ImU32 active_color = ImGui::ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_ButtonHovered]);
                    //
                    //ImGui::BeginChild("##ScrollingRegion", ImVec2(0, ImGui::GetFontSize() * 20), false, ImGuiWindowFlags_HorizontalScrollbar);

                    //// Draw nodes for every animation type
                    //for (auto a = 0; a < _animations[x]->transformNodes.size(); a++) {

                    //    std::string popupId = std::to_string(_animations[x]->transformNodes[a].first.x)
                    //        + std::to_string(_animations[x]->transformNodes[a].first.y)
                    //        + std::to_string(_animations[x]->transformNodes[a].second);

                    //    cursorPos.x += win->Size.x * _animations[x]->transformNodes[a].second / max_time * timeline_radius;
                    //    /*cursorPos.y += timeline_radius;*/

                    //    ImGui::SetCursorScreenPos(cursorPos - ImVec2(timeline_radius, timeline_radius));
                    //    ImGui::PushID(a);

                    //    ImGui::InvisibleButton(std::string(popupId + "invb").c_str(), ImVec2(2*timeline_radius, 2 * timeline_radius));

                    //    //xPos += nodeSize + _animations[x]->transformNodes[a].second * 5.0f; //Normalize time by size grid

                    //    // calc position
                    //    //ImGui::Bullet();
                    //    //ImGui::Dummy(ImVec2(nodeSize, nodeSize));

                    //    //draw_list->AddCircle(ImVec2(p->x + nodeSize, p->y + nodeSize), nodeSize, ImColor(1.0f, 0.0f, 0.0f, 1.0f), 20);
                    //    /*ImVec2 value_with_lock_threshold = ImGui::GetMouseDragDelta(0);
                    //    if (value_with_lock_threshold.x)
                    //        ImGui::Text("Drag delta: x: %.2f y: %.2f", value_with_lock_threshold.x, value_with_lock_threshold.y);*/
                    //    if (ImGui::IsItemHovered()) {
                    //        //draw_list->AddCircleFilled(ImVec2(p->x + nodeSize, p->y + nodeSize), nodeSize, ImColor(1.0f, 0.0f, 0.0f, 1.0f), 20);
                    //        ImGui::BeginTooltip();
                    //        Animation<float>::displayTransformPopup(_animations[x]->transformNodes[a]);
                    //        ImGui::EndTooltip();
                    //    }
                    //    if (ImGui::IsItemActive() && ImGui::IsMouseDragging(0)) {
                    //        _animations[x]->transformNodes[a].second += ImGui::GetIO().MouseDelta.x / win->Size.x * max_time;

                    //    }
                    //    ImGui::PopID();
                    //    draw_list->AddCircleFilled(cursorPos, nodeSize, ImGui::IsItemActive() || ImGui::IsItemHovered() ? active_color : inactive_color);


                    //    if(a != _animations[x]->transformNodes.size())
                    //        ImGui::SameLine();
                    //}

                    //
                    //ImGui::EndChild();  
                    ////ImGui::DragFloat("##Pos", &_animations[x]->pos.x, 0.01f, 0.0f, 100.0f, "%.2f");

                    //ImGui::NextColumn(); // Left
                    //ImGui::Text("Scale");

                    //ImGui::NextColumn(); // Right
                    ////ImGui::DragFloat("##Scale", &_animations[x]->scale.x, 0.01f, 0.0f, 100.0f, "%.2f");

                    //ImGui::NextColumn(); // Left
                    //ImGui::Text("Color");

                    //ImGui::NextColumn(); //Right
                    ///*float* curr_color = &_animations[x]->color.x;
                    //std::string idtext = "Widget " + _animations[x]->name + " color##" + std::to_string(ColorPickerID);
                    //ImGui::ColorEdit4("##ColorPicker", &_animations[x]->color.x, misc_flags);*/

                    //ImGui::NextColumn();

                    ImGui::TreePop();
                }
            }

            // Draw reference time bar
            ImGui::NextColumn();
            /*ImDrawList* draw_list = ImGui::GetWindowDrawList();
            const ImVec2* p = &ImGui::GetCursorScreenPos();
            ImGuiWindow* win = ImGui::GetCurrentWindow();

            ImVec2 cursor = *p;
            for (auto i = 0.0f; i < max_time; i+=0.5f) {
                cursor.x += i * win->Size.x;
                ImGui::SameLine();
                draw_list->AddLine(ImVec2(cursor.x, cursor.y - 2.0f), ImVec2(cursor.x, cursor.y + 2.0f), ImColor(0.0f, 1.0f, 0.0f, 1.0f), 0.2f);
                ImGui::SameLine();
                ImGui::Text("%.2f", i);
            }*/

            ImGui::Columns(1);

            ImGui::TreePop();
        }
        ImGui::End();
    }
    

}

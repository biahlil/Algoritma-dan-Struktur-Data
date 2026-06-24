#include "circle_module.h"
#include "line_module.h"
#include "module.h"
#include "queue_module.h"
#include "stack_module.h"
#include <map>
#include <memory>
#include <vector>

std::vector<MeetingGroup> BuildMeetingGroups() {
  // List All Module
  std::vector<std::shared_ptr<IProjectModule>> all_modules = {
      std::make_shared<LineModule>(), std::make_shared<CircleModule>(),
      std::make_shared<StackModule>(), std::make_shared<QueueModule>()};
  // Kelompokkan menggunakan Map
  std::map<int, MeetingGroup> map_groups;
  for (auto &mod : all_modules) {
    int m_num = mod->GetMeetingNumber();
    // Jika belum ada buatkan
    if (map_groups.find(m_num) == map_groups.end()) {
      map_groups[m_num].meeting_number = m_num;
      map_groups[m_num].meeting_name = mod->GetMeetingName();
    }
    // Masukkan data modul ke grup
    map_groups[m_num].modules.push_back(mod);
    map_groups[m_num].question_names.push_back(mod->GetName());
    map_groups[m_num].input_components.push_back(mod->GetInputComponent());
  }
  // Pindahkan dari Map ke Vector
  std::vector<MeetingGroup> final_groups;
  for (auto const &[key, val] : map_groups) {
    final_groups.push_back(val);
  }

  return final_groups;
}
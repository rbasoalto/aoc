// Uses Google OR Tools for Integer Programming solver.
// 
// Modified from Google OR-Tools examples, under Apache 2.0 License (below)
//
// Copyright 2010-2025 Google LLC
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// [START program]
// [START import]
#include <absl/log/log.h>
#include <bitset>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "ortools/linear_solver/linear_solver.h"
// [END import]

#define MAX_SIZE 15

using bits = std::bitset<MAX_SIZE>;

using counters = std::vector<uint16_t>;

using namespace operations_research;

uint64_t SolveOne(const std::vector<bits>& buttons, const counters& desired) {
  // [START solver]
  // Create the mip solver with the SCIP backend.
  std::unique_ptr<MPSolver> solver(MPSolver::CreateSolver("SCIP"));
  if (!solver) {
    LOG(WARNING) << "SCIP solver unavailable.";
    return 0;
  }
  // [END solver]

  // [START variables]
  std::vector<MPVariable*> button_vars;
  solver->MakeIntVarArray(buttons.size(), 0, solver->infinity(), "button",
                          &button_vars);
  LOG(INFO) << "Number of variables = " << solver->NumVariables();
  // [END variables]

  // [START constraints]
  std::vector<MPConstraint*> constraints;
  for (size_t i = 0; i < desired.size(); ++i) {
    MPConstraint* c = solver->MakeRowConstraint(desired[i], desired[i],
                                                "desired_" + std::to_string(i));

    for (size_t b = 0; b < buttons.size(); ++b) {
      if (buttons[b].test(i)) {
        c->SetCoefficient(button_vars[b], 1);
      }
    }
  }
  LOG(INFO) << "Number of constraints = " << solver->NumConstraints();
  // [END constraints]

  // [START objective]
  MPObjective* const objective = solver->MutableObjective();
  for (auto button_var : button_vars) {
    objective->SetCoefficient(button_var, 1);
  }
  objective->SetMinimization();
  // [END objective]

  // [START solve]
  const MPSolver::ResultStatus result_status = solver->Solve();
  // Check that the problem has an optimal solution.
  if (result_status != MPSolver::OPTIMAL) {
    LOG(FATAL) << "The problem does not have an optimal solution!";
  }
  // [END solve]

  // [START print_solution]
  LOG(INFO) << "Solution:";
  LOG(INFO) << "Optimal objective value = " << objective->Value();
  return static_cast<uint64_t>(std::round(objective->Value()));
  // [END print_solution]
}

void RunAll() {
  uint64_t pushes = 0;
  std::string line;
  while (std::getline(std::cin, line)) {
    std::stringstream ss(line);
    std::string token;
    std::getline(ss, token, ' ');
    std::vector<bits> buttons;

    while (std::getline(ss, token, ' ')) {
      if (token[0] == '{')
        break;
      bits thisbutton;
      std::stringstream ss1(token);
      size_t button;
      char c;
      while (ss1 >> c >> button) {
        thisbutton.flip(button);
      }
      buttons.push_back(std::move(thisbutton));
    }

    // token now contains desired counters
    std::stringstream ss1(token);
    counters desired;
    char c;
    uint16_t ctr;
    while (ss1 >> c >> ctr) {
      desired.push_back(ctr);
    }

    pushes += SolveOne(buttons, desired);
  }
  std::cout << pushes << std::endl;
}

int main(int argc, char** argv) {
  RunAll();
  return 0;
}

// [END program]

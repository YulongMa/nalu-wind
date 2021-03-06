// Copyright 2017 National Technology & Engineering Solutions of Sandia, LLC
// (NTESS), National Renewable Energy Laboratory, University of Texas Austin,
// Northwest Research Associates. Under the terms of Contract DE-NA0003525
// with NTESS, the U.S. Government retains certain rights in this software.
//
// This software is released under the BSD 3-clause license. See LICENSE file
// for more details.
//


#ifndef MOMENTUMSSTTAMSDIFFELEMKERNEL_H
#define MOMENTUMSSTTAMSDIFFELEMKERNEL_H

#include "kernel/Kernel.h"
#include "FieldTypeDef.h"

#include <stk_mesh/base/BulkData.hpp>
#include <stk_mesh/base/Entity.hpp>

#include <Kokkos_Core.hpp>

namespace sierra {
namespace nalu {

class SolutionOptions;
class MasterElement;
class ElemDataRequests;

/** Hybrid turbulence for momentum equation
 *
 */
template <typename AlgTraits>
class MomentumSSTTAMSDiffElemKernel : public NGPKernel<MomentumSSTTAMSDiffElemKernel<AlgTraits>>
{
public:
  MomentumSSTTAMSDiffElemKernel(
    const stk::mesh::BulkData&,
    const SolutionOptions&,
    ScalarFieldType*,
    ElemDataRequests&);

  KOKKOS_FUNCTION MomentumSSTTAMSDiffElemKernel() = default;

  KOKKOS_FUNCTION virtual ~MomentumSSTTAMSDiffElemKernel() = default;

  using Kernel::execute;

  KOKKOS_FUNCTION
  virtual void execute(
    SharedMemView<DoubleType**, DeviceShmem>&,
    SharedMemView<DoubleType*, DeviceShmem>&,
    ScratchViews<DoubleType, DeviceTeamHandleType, DeviceShmem>&);

private:
  unsigned velocityNp1_{stk::mesh::InvalidOrdinal};
  unsigned densityNp1_{stk::mesh::InvalidOrdinal};
  unsigned tkeNp1_{stk::mesh::InvalidOrdinal};
  unsigned sdrNp1_{stk::mesh::InvalidOrdinal};
  unsigned alpha_{stk::mesh::InvalidOrdinal};
  unsigned mutij_{stk::mesh::InvalidOrdinal};
  unsigned coordinates_{stk::mesh::InvalidOrdinal};
  unsigned Mij_{stk::mesh::InvalidOrdinal};

  unsigned avgVelocity_{stk::mesh::InvalidOrdinal};

  unsigned viscosity_{stk::mesh::InvalidOrdinal};

  const double includeDivU_;

  const double betaStar_;
  const double CMdeg_;

  const bool shiftedGradOp_;

  MasterElement* meSCS_{nullptr};
};

} // namespace nalu
} // namespace sierra

#endif /* MOMENTUMSSTTAMSDIFFELEMKERNEL_H */

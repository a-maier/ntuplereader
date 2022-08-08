#include "ntuplereader/nTupleReader.h"
#include <cstddef>

// TODO: catch exceptions & return an error type

extern "C" {
#include "cnTupleReader.h"

nTupleReader *ntuple_reader_new() {
  try {
    return new nTupleReader;
  } catch(...) {
    return nullptr;
  }
}
nTupleReader *ntuple_reader_from_tree(char const *treeName) {
  try {
    return new nTupleReader(treeName);
  } catch(...) {
    return nullptr;
  }
}

BoolResult next_entry(nTupleReader *r) {
  try {
    return { .res = r->nextEntry(), .status = OK};
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}

VoidResult set_pdf(nTupleReader *r, char const *name) {
  try {
    r->setPDF(name);
    return { .status = OK };
  } catch(...) {
    return { .status = ERR };
  }
}

VoidResult set_pdf_member(nTupleReader *r, int member) {
  try {
    r->setPDFmember(member);
    return { .status = OK };
  } catch(...) {
    return { .status = ERR };
  }
}
IntResult get_id(nTupleReader *r) {
  try {
    return { .res = r->getID(), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}
IntResult get_particle_number(nTupleReader *r) {
  try {
    return { .res = r->getParticleNumber(), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}
DoubleResult get_energy(nTupleReader *r, int i) {
  try {
    return { .res = r->getEnergy(i), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
};
DoubleResult get_x(nTupleReader *r, int i) {
  try {
    return { .res = r->getX(i), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}

DoubleResult get_y(nTupleReader *r, int i) {
  try {
    return { .res = r->getY(i), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}

DoubleResult get_z(nTupleReader *r, int i) {
  try {
    return { .res = r->getZ(i), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}

IntResult get_pdg_code(nTupleReader *r, int i) {
  try {
    return { .res = r->getPDGcode(i), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}

DoubleResult get_x1(nTupleReader *r) {
  try {
    return { .res = r->getX1(), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}

DoubleResult get_x2(nTupleReader *r) {
  try {
    return { .res = r->getX2(), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}

DoubleResult get_id1(nTupleReader *r) {
  try {
    return { .res = r->getId1(), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}

DoubleResult get_id2(nTupleReader *r) {
  try {
    return { .res = r->getId2(), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}

ShortResult get_alphas_power(nTupleReader *r) {
  try {
    return { .res = r->getAlphasPower(), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}

DoubleResult get_renormalization_scale(nTupleReader *r) {
  try {
    return { .res = r->getRenormalizationScale(), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}

DoubleResult get_factorization_scale(nTupleReader *r) {
  try {
    return { .res = r->getFactorizationScale(), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}

DoubleResult get_weight(nTupleReader *r) {
  try {
    return { .res = r->getWeight(), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}

DoubleResult get_weight2(nTupleReader *r) {
  try {
    return { .res = r->getWeight2(), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}

DoubleResult get_me_weight(nTupleReader *r) {
  try {
    return { .res = r->getMEWeight(), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}

DoubleResult get_me_weight2(nTupleReader *r) {
  try {
    return { .res = r->getMEWeight2(), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}

CharResult get_type(nTupleReader *r) {
  try {
    return { .res = r->getType(), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}

DoubleResult compute_weight(
  nTupleReader *r, double newFactorizationScale,
  double newRenormalizationScale
) {
  try {
    return { .res = r->computeWeight(newFactorizationScale, newRenormalizationScale), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}

DoubleResult compute_weight2(
  nTupleReader *r, double newFactorizationScale,
  double newRenormalizationScale
) {
  try {
    return { .res = r->computeWeight2(newFactorizationScale, newRenormalizationScale), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}

VoidResult set_pp(nTupleReader *r) {
  try {
    r->setPP();
    return { .status = OK };
  } catch(...) {
    return { .status = ERR };
  }
}

VoidResult set_ppbar(nTupleReader *r) {
  try {
    r->setPPbar();
    return { .status = OK };
  } catch(...) {
    return { .status = ERR };
  }
}


void drop_ntuple_reader(nTupleReader *r) {
  delete r;
}

VoidResult add_file(nTupleReader *r, char const *filename) {
  try {
    r->addFile(filename);
    return { .status = OK };
  } catch(...) {
    return { .status = ERR };
  }
}

// VoidResult set_cms_energy(nTupleReader *r, double CMS_energy) {
//   try {
//     r->setCMSEnergy(CMS_energy);
//     return {  .status = OK };
//   } catch(...) {
//     return { .res = {}, .status = ERR };
//   }
// }
// VoidResult set_collider_type(nTupleReader *r, ColliderType ct) {
//   try {
//     r->setColliderType(static_cast<colliderType>(ct));
//     return { .status = OK };
//   } catch(...) {
//     return { .res = {}, .status = ERR };
//   }
// }
VoidResult reset_cross_section(nTupleReader *r) {
  try {
    r->resetCrossSection();
    return { .status = OK };
  } catch(...) {
    return { .status = ERR };
  }
}
DoubleResult get_cross_section(nTupleReader *r) {
  try {
    return { .res = r->getCrossSection(), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}
DoubleResult get_cross_section_error(nTupleReader *r) {
  try {
    return { .res = r->getCrossSectionError(), .status = OK };
  } catch(...) {
    return { .res = {}, .status = ERR };
  }
}
}

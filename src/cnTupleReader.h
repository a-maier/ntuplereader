#pragma once
//! C wrapper around Daniel's nTupleReader
#include <stdbool.h>

typedef enum { PP, PPBAR } ColliderType;

typedef struct nTupleReader nTupleReader;

typedef enum {
  OK = 0,
  ERR = 1,
}  Status;

typedef struct {
  bool res;
  Status status;
} BoolResult;

typedef struct {
  Status status;
} VoidResult;

typedef struct {
  double res;
  Status status;
} DoubleResult;

typedef struct {
  int res;
  Status status;
} IntResult;

typedef struct {
  short res;
  Status status;
} ShortResult;

typedef struct {
  char res;
  Status status;
} CharResult;

//! Constructor for a nTupleReader object
nTupleReader *ntuple_reader_new();
nTupleReader *ntuple_reader_from_tree(char const *tree_name);

/**
   Reads the next entry and returns true upon success, false otherwise
   (including when the end of the file is reached).
*/

BoolResult next_entry(nTupleReader *r);

/** Sets the pdf set to be used.
    \param name is the name of the file to be loaded by \\textsc{LHAPDF}, for
   example {\\tt CT10.LHgrid\/}.
*/
VoidResult set_pdf(nTupleReader *r, char const *name);

/** Sets the pdf member number to be used.
\param member is an integer labeling the member;
0 is typically used to denote the central value.
*/
VoidResult set_pdf_member(nTupleReader *r, int member);
/** Returns the ID of the current event.
 *
 */
IntResult get_id(nTupleReader *r);
/** Returns the number of final state particles in the current entry.
 */
IntResult get_particle_number(nTupleReader *r);
/** Returns the energy of the $i^{\rm th}$ particle in the current entry.
        \param i is a 0-based index; an argument equal to or larger than the
number of final state particles will throw an {\\tt nTR\\\_OutOfBound\/}
exception.
*/
DoubleResult get_energy(nTupleReader *r, int i);
;
/** Returns the $x$ component of the $i^{\rm th}$ particle's momentum in the
current entry. \param i is a 0-based index; an argument equal to or larger than
the number of final state particles will throw an {\\tt nTR\\\_OutOfBound\/}
exception.
*/
DoubleResult get_x(nTupleReader *r, int i);
/** Returns the $y$ component of the $i^{\rm th}$ particle's momentum in the
current entry. \param i is a 0-based index; an argument equal to or larger than
the number of final state particles will throw an {\\tt nTR\\\_OutOfBound\/}
exception.
*/
DoubleResult get_y(nTupleReader *r, int i);
/** Returns the $z$ component of the $i^{\rm th}$ particle's momentum in the
current entry. \param i is a 0-based index; an argument equal to or larger than
the number of final state particles will throw an {\\tt nTR\\\_OutOfBound\/}
exception.
*/
DoubleResult get_z(nTupleReader *r, int i);
/** Returns the PDG code of the $i^{\rm th}$ particle in the current entry.
        \param i is a 0-based index; an argument equal to or larger than the
number of final state particles will throw an {\\tt nTR\\\_OutOfBound\/}
exception.
*/
IntResult get_pdg_code(nTupleReader *r, int i);
/** Returns the momentum fraction $x_1$ in the current entry.
 */
DoubleResult get_x1(nTupleReader *r);
/** Returns the momentum fraction $x_2$ in the current entry.
 */
DoubleResult get_x2(nTupleReader *r);
/** Returns the PDG code for the first (forward) incoming parton in the current
 * entry.
 */
DoubleResult get_id1(nTupleReader *r);
/** Returns the PDG code for the second (backward) incoming parton in the
 * current entry.
 */
DoubleResult get_id2(nTupleReader *r);
/** Returns the power of the strong coupling constant in the current entry.
 */
ShortResult get_alphas_power(nTupleReader *r);
/** Returns the renormalization scale used to compute the weights for the
 * current entry.
 */
DoubleResult get_renormalization_scale(nTupleReader *r);
/** Returns the factorization scale used to compute the weights for the current
 * entry.
 */
DoubleResult get_factorization_scale(nTupleReader *r);
/** Returns the weight ({\\tt weight\/}) for the current entry.
 */
DoubleResult get_weight(nTupleReader *r);
/** Returns the secondary weight ({\\tt weight2\/}) for the current entry, to be
 * used as described in \\sect{NTupleUseSection} to obtain the correct estimate
 * of the statistical uncertainty.
 */
DoubleResult get_weight2(nTupleReader *r);
/** Returns the weight for the current entry omitting pdf factors.
 */
DoubleResult get_me_weight(nTupleReader *r);
/** Returns the secondary weight for the current entry omitting the pdf factors,
 * to be used as described in \\sect{NTupleUseSection} to obtain the correct
 * estimate of the statistical uncertainty.
 */
DoubleResult get_me_weight2(nTupleReader *r);
/** Returns the type of the current entry, `B' standing for born, `I' for
integrated subtraction, `V' for the virtual, and `R' for the subtracted real
emission.
*/
CharResult get_type(nTupleReader* r);
/** Returns the weight ({\\tt weight\/}) of the current entry
 * recomputed for the new scales, using the current pdf member number in the
 * current pdf set. \param newFactorizationScale is the new factorization scale
 * (in GeV) \param newRenormalisationScale is the new renormalization scale (in
 * GeV)
 */
DoubleResult compute_weight(
  nTupleReader *r,
  double new_factorization_scale,
  double new_renormalization_scale
);
/** Returns the secondary weight ({\\tt weight2\/}) of the current entry
 * recomputed for the new scales, using the current pdf member number in the
 * current pdf set. One should use this weight for the real part in order to
 * take into account the correlation between the entry and counter entries.
 * \param newFactorizationScale is the new factorization scale (in GeV)
 * \param newRenormalisationScale is the new renormalization scale (in GeV)
 */
DoubleResult compute_weight2(
  nTupleReader *r,
  double new_factorization_scale,
  double new_renormalization_scale
);
/** Sets the initial state to proton\--proton. This is the default if no calls
 * to {\\tt setPP()} or {\\tt setPPbar\(\)} are issued. This routine should only
 * be invoked before using files generated for proton\--proton colliders.
 * */
VoidResult set_pp(nTupleReader *r);
/** Sets the initial state to proton\--antiproton. This routine should only be
 * invoked before using files generated for proton\--antiproton colliders.
 * */
VoidResult set_ppbar(nTupleReader *r);
//! Destructor

void drop_ntuple_reader(nTupleReader *r);

VoidResult add_file(nTupleReader* r, char const *filename);

VoidResult reset_cross_section(nTupleReader *r);
DoubleResult get_cross_section(nTupleReader *r);
DoubleResult get_cross_section_error(nTupleReader *r);

/* only with HepMC support, see nTupleReader_impl.h */
/* void set_cms_energy(nTupleReader *r, double cms_energy); */
/* void set_collider_type(nTupleReader *r, ColliderType ct); */

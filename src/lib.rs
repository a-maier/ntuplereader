use std::os::raw::{c_char, c_short, c_int};
use std::{ffi::CString, path::Path};
use std::os::unix::ffi::OsStrExt;

#[derive(Debug)]
pub struct NTupleReader (
    *mut nTupleReader
);

impl Default for NTupleReader {
    fn default() -> Self {
        let res = unsafe { ntuple_reader_new() };
        assert!(!res.is_null());
        Self( res )
    }
}

impl From<VoidResult> for () {
    fn from(res: VoidResult) -> Self {
        if res.status != Status::OK {
            panic!("Exception in nTupleReader");
        }
    }
}

macro_rules! from_res {
    ( $from:ty, $to: ty ) => {
        impl From<$from> for $to {
            fn from(res: $from) -> $to {
                if res.status != Status::OK {
                    panic!("Exception in nTupleReader");
                }
                res.res
            }
        }
    }
}

from_res!(BoolResult, bool);
from_res!(CharResult, c_char);
from_res!(ShortResult, c_short);
from_res!(IntResult, c_int);
from_res!(DoubleResult, f64);

impl NTupleReader {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn from_tree<T: AsRef<str>>(name: T) -> Self {
        let name = CString::new(name.as_ref()).unwrap();
        Self( unsafe { ntuple_reader_from_tree(name.as_ptr()) } )
    }

    pub fn next_entry(&mut self) -> bool {
        unsafe { next_entry(self.0) }.into()
    }

    pub fn set_pdf<T: AsRef<str>>(&mut self, name: T) {
        let name = CString::new(name.as_ref()).unwrap();
        unsafe { set_pdf(self.0, name.as_ptr()) }.into()
    }

    pub fn set_pdf_member(&mut self, member: i32) {
        unsafe { set_pdf_member(self.0, member.into()) }.into()
    }

    pub fn get_id(&mut self) -> i32 {
        unsafe { get_id(self.0) }.into()
    }

    pub fn get_particle_number(&mut self) -> i32 {
        unsafe { get_particle_number(self.0) }.into()
    }

    pub fn get_energy(&mut self, i: i32) -> f64 {
        unsafe { get_energy(self.0, i.into()) }.into()
    }

    pub fn get_x(&mut self, i: i32) -> f64 {
        unsafe { get_x(self.0, i.into()) }.into()
    }

    pub fn get_y(&mut self, i: i32) -> f64 {
        unsafe { get_y(self.0, i.into()) }.into()
    }

    pub fn get_z(&mut self, i: i32) -> f64 {
        unsafe { get_z(self.0, i.into()) }.into()
    }

    pub fn get_pdg_code(&mut self, i: i32) -> i32 {
        unsafe { get_pdg_code(self.0, i.into()) }.into()
    }

    pub fn get_x1(&mut self) -> f64 {
        unsafe { get_x1(self.0) }.into()
    }

    pub fn get_x2(&mut self) -> f64 {
        unsafe { get_x2(self.0) }.into()
    }

    pub fn get_id1(&mut self) -> f64 {
        unsafe { get_id1(self.0) }.into()
    }

    pub fn get_id2(&mut self) -> f64 {
        unsafe { get_id2(self.0) }.into()
    }

    pub fn get_alphas_power(&mut self) -> i16 {
        unsafe { get_alphas_power(self.0) }.into()
    }

    pub fn get_renormalization_scale(&mut self) -> f64 {
        unsafe { get_renormalization_scale(self.0) }.into()
    }

    pub fn get_factorization_scale(&mut self) -> f64 {
        unsafe { get_factorization_scale(self.0) }.into()
    }

    pub fn get_weight(&mut self) -> f64 {
        unsafe { get_weight(self.0) }.into()
    }

    pub fn get_weight2(&mut self) -> f64 {
        unsafe { get_weight2(self.0) }.into()
    }

    pub fn get_me_weight(&mut self) -> f64 {
        unsafe { get_me_weight(self.0) }.into()
    }

    pub fn get_me_weight2(&mut self) -> f64 {
        unsafe { get_me_weight2(self.0) }.into()
    }

    pub fn get_type(&mut self) -> i8 {
        unsafe { get_type(self.0) }.into()
    }

    pub fn compute_weight(
        &mut self,
        new_factorization_scale: f64,
        new_renormalization_scale: f64,
    ) -> f64 {
        unsafe { compute_weight(self.0, new_factorization_scale, new_renormalization_scale) }.into()
    }

    pub fn compute_weight2(
        &mut self,
        new_factorization_scale: f64,
        new_renormalization_scale: f64,
    ) -> f64 {
        unsafe { compute_weight2(self.0, new_factorization_scale, new_renormalization_scale) }.into()
    }

    pub fn set_pp(&mut self) {
        unsafe { set_pp(self.0) }.into()
    }

    pub fn set_ppbar(&mut self) {
        unsafe { set_pp(self.0) }.into()
    }

    pub fn add_file<T: AsRef<Path>>(&mut self, name: T) {
        let name = CString::new(name.as_ref().as_os_str().as_bytes()).unwrap();
        unsafe {
            add_file(self.0, name.as_ptr())
        }.into()
    }

    // pub fn set_cms_energy(&mut self, cms_energy: f64) {
    //     unsafe { set_cms_energy(self.0, cms_energy) }.into()
    // }

    // pub fn set_collider_type(&mut self, ct: ColliderType) {
    //     unsafe { set_collider_type(self.0, ct) }.into()
    // }

    pub fn reset_cross_section(&mut self) {
        unsafe { reset_cross_section(self.0) }.into()
    }

    pub fn get_cross_section(&mut self) -> f64 {
        unsafe { get_cross_section(self.0) }.into()
    }

    pub fn get_cross_section_error(&mut self) -> f64 {
        unsafe { get_cross_section_error(self.0) }.into()
    }
}

impl Drop for NTupleReader {
    fn drop(&mut self) {
        unsafe { drop_ntuple_reader(self.0) }.into()
    }
}

include!(concat!(env!("OUT_DIR"), "/ntuplereader.rs"));

#[cfg(test)]
mod tests {
    use std::{process::Command, path::PathBuf, str::from_utf8};

    use super::*;


    fn get_example_path() -> PathBuf {
        const CFG_CMD: &str = "nTupleReader-config";
        const PREFIX_ARG: &str = "--prefix";

        let output = Command::new(CFG_CMD).arg(PREFIX_ARG).output().unwrap();
        let basedir = from_utf8(&output.stdout).unwrap();
        [basedir.trim(), "share", "ntuplereader"].iter().collect()
    }

    // Daniel's ntuplereader example
    #[test]
    fn ex() {
        let mut r = NTupleReader::new();

        r.set_pdf("MMHT2014nlo68cl");
        let mut example_file = get_example_path();
        example_file.push("sample.root");
	r.add_file(example_file);

	while r.next_entry(){
	    let id = r.get_id();
            println!("Checking momentum conservation for event ID: {id}");
            let mut sum_x = 0.;
            let mut sum_y = 0.;
            let mut sum_z = 0.;

            let npart = r.get_particle_number();

            for i in 0..npart {
                sum_x += r.get_x(i);
                sum_y += r.get_y(i);
                sum_z += r.get_z(i);
            }

            println!("Sum x: {sum_x}");
            assert_eq!(sum_x, 0.);
            println!("Sum y: {sum_y}");
            assert_eq!(sum_y, 0.);
            println!("Sum z: {sum_z}");
            let ref_sum_z = 3500. * (r.get_x1() - r.get_x2());
            println!("To be compared with: {ref_sum_z}", );
            assert!(((sum_z - ref_sum_z) / ref_sum_z).abs() < 1e-7);
	}
    }
}

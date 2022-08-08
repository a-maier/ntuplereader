pub mod ntuplereader;

pub use ntuplereader::NTupleReader;

include!(concat!(env!("OUT_DIR"), "/flags.rs"));

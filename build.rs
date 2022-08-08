use std::{path::PathBuf, env};
use anyhow::Result;

fn main() -> Result<()> {
    compile_ntuple_reader()
}

fn compile_ntuple_reader() -> Result<()> {
    let bindings = bindgen::Builder::default()
        .header("src/cnTupleReader.h")
        .parse_callbacks(Box::new(bindgen::CargoCallbacks))
        .blocklist_item("true_")
        .blocklist_item("false_")
        .blocklist_item("__bool_true_false_are_defined")
        .newtype_enum("ColliderType")
        .newtype_enum("Status")
        .generate()
        .expect("Failed to generate ntuple reader bindings");

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("ntuplereader.rs"))
        .expect("Failed to write ntuple reader bindings!");

    println!("cargo:rerun-if-changed=src/cnTupleReader.h");
    println!("cargo:rerun-if-changed=src/cnTupleReader.cc");
    let mut cc_cmd = cc::Build::new();
    cc_cmd
        .cpp(true)
        .file("src/cnTupleReader.cc");

    for flag in get_ntuplereader_flags("--cxxflags")? {
        cc_cmd.flag(&flag);
    }

    cc_cmd.compile("cntuplereader");

    let linker_flags = get_ntuplereader_flags("--rpath")?.into_iter().chain(
        get_ntuplereader_flags("--ldflags")?.into_iter()
    ).chain(
        get_ntuplereader_flags("--libs")?.into_iter()
    );
    for flag in linker_flags {
        println!("cargo:rustc-link-arg={flag}");
    }
    Ok(())
}

fn get_ntuplereader_flags(flags: &str) -> Result<Vec<String>> {
    use std::{process::Command, str::from_utf8};
    use anyhow::{anyhow, Context};

    const CFG_CMD: &str = "nTupleReader-config";

    let cmd = format!("{CFG_CMD} {flags}");
    let output = Command::new(CFG_CMD).arg(flags).output().with_context(
        || format!("Failed to run `{cmd}`")
    )?;
    if !output.status.success() {
        if output.stderr.is_empty() {
            return Err(
                anyhow!("{CFG_CMD} {flags} failed without error messages")
            );
        } else {
            return Err(anyhow!(
                "{CFG_CMD} {flags} failed: {}",
                from_utf8(&output.stderr).unwrap()
            ));
        }
    }
    let args = from_utf8(&output.stdout).with_context(
        || format!("Failed to convert `{cmd}` output to utf8")
    )?;
    Ok(args.split_whitespace().map(|arg| arg.to_owned()).collect())
}

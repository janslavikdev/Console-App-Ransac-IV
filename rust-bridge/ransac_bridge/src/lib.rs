use cxx::CxxString;
use cxx::UniquePtr;
use std::pin::Pin;

#[cxx::bridge]
mod ffi {
    unsafe extern "C++" {
        include!("ransac_bridge/include/ransac_bridge.h");
        type RansacFitResultDTO;

        fn initialize_from_csv(path: &CxxString) -> UniquePtr<RansacFitResultDTO>;

        //fn run_ransac(table: Pin<&mut Table>, threshold: f64) -> f64;
    }
}

pub use ffi::{initialize_from_csv, RansacFitResultDTO};


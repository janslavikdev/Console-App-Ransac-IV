use cxx::CxxString;
use cxx::UniquePtr;
use std::pin::Pin;

#[cxx::bridge]
mod ffi {
    unsafe extern "C++" {
        include!("ransac_bridge/include/ransac_bridge.h");
        type AppState;
        type RansacFitResultDTO;

        fn create_app_state() -> UniquePtr<AppState>;
        fn initialize_from_csv(state: Pin<&mut AppState>, path: &CxxString) -> UniquePtr<RansacFitResultDTO>;

        //fn change_ransac_parameters(table: Pin<&mut Table>, threshold: f64) -> f64;
    }
}

pub use ffi::{create_app_state, initialize_from_csv, AppState, RansacFitResultDTO};

pub struct RansacBridge {
    state: UniquePtr<AppState>,
}

impl RansacBridge {
    pub fn new() -> Self {
        Self {
            state: create_app_state(),
        }
    }

    pub fn with_state(state: UniquePtr<AppState>) -> Self {
        Self { state }
    }

    pub fn state_mut(&mut self) -> Pin<&mut AppState> {
        self.state.pin_mut()
    }

    pub fn initialize_from_csv(&mut self, path: &str) -> UniquePtr<RansacFitResultDTO> {
        cxx::let_cxx_string!(cxx_path = path);
        initialize_from_csv(self.state.pin_mut(), &cxx_path)
    }
}

impl Default for RansacBridge {
    fn default() -> Self {
        Self::new()
    }
}


use audiopus::Application;
use ext_php_rs::{
    info_table_end, info_table_row, info_table_start,
    php::{
        constants::IntoConst,
        enums::DataType,
        function::FunctionBuilder,
        module::{ModuleBuilder, ModuleEntry},
    },
};

use crate::encoder::OpusEncoder;

#[no_mangle]
pub extern "C" fn get_module() -> *mut ModuleEntry {
    let opus_version = FunctionBuilder::new("opus_version", super::functions::opus_version)
        .returns(DataType::String, false, false)
        .build();

    ModuleBuilder::new("opus", env!("CARGO_PKG_VERSION"))
        .info_function(opus_info)
        .startup_function(opus_module_startup)
        .function(opus_version)
        .build()
        .into_raw()
}

pub extern "C" fn opus_info(_module: *mut ModuleEntry) {
    info_table_start!();
    info_table_row!("Opus Version", audiopus::version());
    info_table_end!();
}

pub extern "C" fn opus_module_startup(_type: i32, module_number: i32) -> i32 {
    OpusEncoder::build_class_object();

    // Register constants
    (Application::Voip as i32).register_constant("OPUS_APPLICATION_VOIP", module_number);
    (Application::Audio as i32).register_constant("OPUS_APPLICATION_AUDIO", module_number);
    (Application::LowDelay as i32)
        .register_constant("OPUS_APPLICATION_RESTRICTED_LOWDELAY", module_number);

    0
}

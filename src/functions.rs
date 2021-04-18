use ext_php_rs::php::{execution_data::ExecutionData, types::zval::Zval};

/// Returns the version of Opus that the extension is using.
pub extern "C" fn opus_version(_: &mut ExecutionData, retval: &mut Zval) {
    retval.set_string(audiopus::version())
}

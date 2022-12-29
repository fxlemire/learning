<?php

/*
 * System settings form for blacklisting passwords
 */
function form_alter_passwords_form($form, &$form_state) {
  $form['form_alter_badpasswords'] = array(
    '#type' => 'textfield',
    '#title' => t('Bad Passwords'),
    '#default_value' => variable_get('form_alter_badpasswords'),
    '#description' => t('Enter a list of "bad passwords" separated by commas. If a user tries to enter one of these passwords either on account creation or when editing their account, the form will display an error message.')
  );

  return system_settings_form($form);
}

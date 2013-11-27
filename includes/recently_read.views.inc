<?php

/**
 * Implements of hook_views_data().
 **/
function recently_read_views_data() {
  $data['recently_read_nodes']['table']['group'] = t('Recently Read');
  $data['recently_read_nodes']['table']['base'] = array(
    'field' => 'nid',
    'title' => t('Recently read'),
    'help' => t('Recently Read')
  );
  $data['recently_read_nodes']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    )
  );

  $data['recently_read_nodes']['uid'] = array(
    'title' => t('Recently Read uid'),
    'help' => t('Recently Read uid'),
    'field' => array(
      'handler' => 'views_handler_field_user',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_user_name',
    ),
    'relationship' => array(
      'base' => 'users',
      'base field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('Recently Read User'),
      'title' => t('Relationship uid'),
      'help' => t('Relationship to users'),
    ),
  );

  $data['recently_read_nodes']['current_user'] = array(
    'real field' => 'uid',
    'title' => t('Current'),
    'help' => t('Filter the view to the currently logged in user.'),
    'filter' => array(
      'handler' => 'views_handler_filter_rr_user',
      'type' => 'yes-no',
    ),
  );

  $data['recently_read_nodes']['timestamp'] = array(
    'title' => t('Recently Read Date'),
    'help' => t('Recently Read Time'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  return $data;
}

/**
 * Implements of hook_views_data_alter().
 **/
function recently_read_views_data_alter(&$data) {
  $data['node']['rid'] = array(
    'title' => t('Recently Read'),
    'help' => t('Recently Read Relationship'),
    'filter' => array(
      'handler' => 'views_handler_filter_rr_nid',
    ),
    'relationship' => array(
      'group' => 'Recently Read',
      'label' => t('Recently Read'),
      'base' => 'recently_read_nodes',
      'base field' => 'nid',
      'relationship field' => 'nid',
      'handler' => 'views_handler_relationship'
    ),
  );
}

/**
 * Implement hook_views_default_views();
 **/
function recently_read_views_default_views() {
	$view = new view();
	$view->name = 'recently_read';
	$view->description = '';
	$view->tag = 'default';
	$view->base_table = 'node';
	$view->human_name = 'Recently Read';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

	/* Display: Master */
	$handler = $view->new_display('default', 'Master', 'default');
	$handler->display->display_options['title'] = 'Recently Read';
	$handler->display->display_options['use_more_always'] = FALSE;
	$handler->display->display_options['access']['type'] = 'perm';
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['pager']['type'] = 'full';
	$handler->display->display_options['pager']['options']['items_per_page'] = '10';
	$handler->display->display_options['style_plugin'] = 'list';
	$handler->display->display_options['row_plugin'] = 'fields';
	/* Relationship: Recently Read: Relationship uid */
	$handler->display->display_options['relationships']['uid']['id'] = 'uid';
	$handler->display->display_options['relationships']['uid']['table'] = 'recently_read_nodes';
	$handler->display->display_options['relationships']['uid']['field'] = 'uid';
	/* Field: Content: Title */
	$handler->display->display_options['fields']['title']['id'] = 'title';
	$handler->display->display_options['fields']['title']['table'] = 'node';
	$handler->display->display_options['fields']['title']['field'] = 'title';
	$handler->display->display_options['fields']['title']['label'] = '';
	$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
	$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
	/* Sort criterion: Content: Post date */
	$handler->display->display_options['sorts']['created']['id'] = 'created';
	$handler->display->display_options['sorts']['created']['table'] = 'node';
	$handler->display->display_options['sorts']['created']['field'] = 'created';
	$handler->display->display_options['sorts']['created']['order'] = 'DESC';
	/* Contextual filter: Content: Nid */
	$handler->display->display_options['arguments']['nid']['id'] = 'nid';
	$handler->display->display_options['arguments']['nid']['table'] = 'node';
	$handler->display->display_options['arguments']['nid']['field'] = 'nid';
	$handler->display->display_options['arguments']['nid']['default_action'] = 'default';
	$handler->display->display_options['arguments']['nid']['default_argument_type'] = 'rr';
	$handler->display->display_options['arguments']['nid']['default_argument_skip_url'] = TRUE;
	$handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
	$handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
	$handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
	$handler->display->display_options['arguments']['nid']['break_phrase'] = TRUE;
	/* Filter criterion: Recently Read: Current */
	$handler->display->display_options['filters']['current_user']['id'] = 'current_user';
	$handler->display->display_options['filters']['current_user']['table'] = 'recently_read_nodes';
	$handler->display->display_options['filters']['current_user']['field'] = 'current_user';
	$handler->display->display_options['filters']['current_user']['value'] = '1';

	/* Display: Page */
	$handler = $view->new_display('page', 'Page', 'page');
	$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
	$handler->display->display_options['defaults']['style_plugin'] = FALSE;
	$handler->display->display_options['style_plugin'] = 'table';
	$handler->display->display_options['style_options']['columns'] = array(
		'title' => 'title',
		'uid' => 'uid',
		'name' => 'name',
	);
	$handler->display->display_options['style_options']['default'] = '-1';
	$handler->display->display_options['style_options']['info'] = array(
		'title' => array(
			'sortable' => 0,
			'default_sort_order' => 'asc',
			'align' => '',
			'separator' => '',
			'empty_column' => 0,
		),
		'uid' => array(
			'sortable' => 0,
			'default_sort_order' => 'asc',
			'align' => '',
			'separator' => '',
			'empty_column' => 0,
		),
		'name' => array(
			'sortable' => 0,
			'default_sort_order' => 'asc',
			'align' => '',
			'separator' => '',
			'empty_column' => 0,
		),
	);
	$handler->display->display_options['defaults']['style_options'] = FALSE;
	$handler->display->display_options['defaults']['row_plugin'] = FALSE;
	$handler->display->display_options['defaults']['row_options'] = FALSE;
	$handler->display->display_options['defaults']['relationships'] = FALSE;
	/* Relationship: Recently Read: Relationship uid */
	$handler->display->display_options['relationships']['uid']['id'] = 'uid';
	$handler->display->display_options['relationships']['uid']['table'] = 'recently_read_nodes';
	$handler->display->display_options['relationships']['uid']['field'] = 'uid';
	$handler->display->display_options['defaults']['fields'] = FALSE;
	/* Field: Content: Title */
	$handler->display->display_options['fields']['title']['id'] = 'title';
	$handler->display->display_options['fields']['title']['table'] = 'node';
	$handler->display->display_options['fields']['title']['field'] = 'title';
	$handler->display->display_options['fields']['title']['label'] = '';
	$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
	$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
	$handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
	/* Field: Recently Read: Recently Read uid */
	$handler->display->display_options['fields']['uid']['id'] = 'uid';
	$handler->display->display_options['fields']['uid']['table'] = 'recently_read_nodes';
	$handler->display->display_options['fields']['uid']['field'] = 'uid';
	$handler->display->display_options['fields']['uid']['exclude'] = TRUE;
	/* Field: User: Name */
	$handler->display->display_options['fields']['name']['id'] = 'name';
	$handler->display->display_options['fields']['name']['table'] = 'users';
	$handler->display->display_options['fields']['name']['field'] = 'name';
	$handler->display->display_options['fields']['name']['relationship'] = 'uid';
	$handler->display->display_options['defaults']['filter_groups'] = FALSE;
	$handler->display->display_options['defaults']['filters'] = FALSE;
	/* Filter criterion: Recently Read: Current */
	$handler->display->display_options['filters']['current_user']['id'] = 'current_user';
	$handler->display->display_options['filters']['current_user']['table'] = 'recently_read_nodes';
	$handler->display->display_options['filters']['current_user']['field'] = 'current_user';
	$handler->display->display_options['filters']['current_user']['exposed'] = TRUE;
	$handler->display->display_options['filters']['current_user']['expose']['operator_id'] = '';
	$handler->display->display_options['filters']['current_user']['expose']['label'] = 'Is the logged in user';
	$handler->display->display_options['filters']['current_user']['expose']['operator'] = 'current_user_op';
	$handler->display->display_options['filters']['current_user']['expose']['identifier'] = 'current_user';
	$handler->display->display_options['filters']['current_user']['expose']['remember_roles'] = array(
		2 => '2',
		1 => 0,
		3 => 0,
	);
	/* Filter criterion: User: Name */
	$handler->display->display_options['filters']['uid']['id'] = 'uid';
	$handler->display->display_options['filters']['uid']['table'] = 'users';
	$handler->display->display_options['filters']['uid']['field'] = 'uid';
	$handler->display->display_options['filters']['uid']['relationship'] = 'uid';
	$handler->display->display_options['filters']['uid']['value'] = '';
	$handler->display->display_options['filters']['uid']['exposed'] = TRUE;
	$handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
	$handler->display->display_options['filters']['uid']['expose']['label'] = 'Name';
	$handler->display->display_options['filters']['uid']['expose']['use_operator'] = TRUE;
	$handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
	$handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
	$handler->display->display_options['filters']['uid']['expose']['remember_roles'] = array(
		2 => '2',
		1 => 0,
		3 => 0,
	);
	$handler->display->display_options['path'] = 'admin/config/system/recently-read/list';
	$handler->display->display_options['menu']['type'] = 'tab';
	$handler->display->display_options['menu']['title'] = 'Recently Read';
	$handler->display->display_options['menu']['weight'] = '0';
	$handler->display->display_options['menu']['context'] = 1;
	$handler->display->display_options['tab_options']['type'] = 'tab';
	$handler->display->display_options['tab_options']['title'] = 'Recently Read';
	$handler->display->display_options['tab_options']['weight'] = '0';

	/* Display: Block */
	$handler = $view->new_display('block', 'Block', 'block_1');
	$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
	$handler->display->display_options['defaults']['style_plugin'] = FALSE;
	$handler->display->display_options['style_plugin'] = 'grid';
	$handler->display->display_options['defaults']['style_options'] = FALSE;
	$handler->display->display_options['defaults']['row_plugin'] = FALSE;
	$handler->display->display_options['row_plugin'] = 'node';
	$handler->display->display_options['defaults']['row_options'] = FALSE;
	
	$views[$view->name] = $view;
  return $views;
}
